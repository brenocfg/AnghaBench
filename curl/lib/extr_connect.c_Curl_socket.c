#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in6 {scalar_t__ sin6_scope_id; } ;
struct curl_sockaddr {int dummy; } ;
struct connectdata {scalar_t__ transport; scalar_t__ scope_id; struct Curl_easy* data; } ;
struct Curl_sockaddr_storage {int dummy; } ;
struct Curl_sockaddr_ex {scalar_t__ family; int addrlen; int /*<<< orphan*/  sa_addr; int /*<<< orphan*/  protocol; int /*<<< orphan*/  socktype; } ;
struct TYPE_4__ {scalar_t__ (* fopensocket ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct curl_sockaddr*) ;int /*<<< orphan*/  opensocket_client; } ;
struct Curl_easy {TYPE_1__ set; } ;
typedef  scalar_t__ curl_socket_t ;
struct TYPE_5__ {scalar_t__ ai_family; int ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_protocol; } ;
typedef  TYPE_2__ Curl_addrinfo ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  CURLE_COULDNT_CONNECT ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLSOCKTYPE_IPCXN ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_set_in_callback (struct Curl_easy*,int) ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ TRNSPRT_QUIC ; 
 scalar_t__ TRNSPRT_TCP ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  curlx_nonblock (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct curl_sockaddr*) ; 

CURLcode Curl_socket(struct connectdata *conn,
                     const Curl_addrinfo *ai,
                     struct Curl_sockaddr_ex *addr,
                     curl_socket_t *sockfd)
{
  struct Curl_easy *data = conn->data;
  struct Curl_sockaddr_ex dummy;

  if(!addr)
    /* if the caller doesn't want info back, use a local temp copy */
    addr = &dummy;

  /*
   * The Curl_sockaddr_ex structure is basically libcurl's external API
   * curl_sockaddr structure with enough space available to directly hold
   * any protocol-specific address structures. The variable declared here
   * will be used to pass / receive data to/from the fopensocket callback
   * if this has been set, before that, it is initialized from parameters.
   */

  addr->family = ai->ai_family;
  addr->socktype = (conn->transport == TRNSPRT_TCP) ? SOCK_STREAM : SOCK_DGRAM;
  addr->protocol = conn->transport != TRNSPRT_TCP ? IPPROTO_UDP :
    ai->ai_protocol;
  addr->addrlen = ai->ai_addrlen;

  if(addr->addrlen > sizeof(struct Curl_sockaddr_storage))
     addr->addrlen = sizeof(struct Curl_sockaddr_storage);
  memcpy(&addr->sa_addr, ai->ai_addr, addr->addrlen);

  if(data->set.fopensocket) {
   /*
    * If the opensocket callback is set, all the destination address
    * information is passed to the callback. Depending on this information the
    * callback may opt to abort the connection, this is indicated returning
    * CURL_SOCKET_BAD; otherwise it will return a not-connected socket. When
    * the callback returns a valid socket the destination address information
    * might have been changed and this 'new' address will actually be used
    * here to connect.
    */
    Curl_set_in_callback(data, true);
    *sockfd = data->set.fopensocket(data->set.opensocket_client,
                                    CURLSOCKTYPE_IPCXN,
                                    (struct curl_sockaddr *)addr);
    Curl_set_in_callback(data, false);
  }
  else
    /* opensocket callback not set, so simply create the socket now */
    *sockfd = socket(addr->family, addr->socktype, addr->protocol);

  if(*sockfd == CURL_SOCKET_BAD)
    /* no socket, no connection */
    return CURLE_COULDNT_CONNECT;

  if(conn->transport == TRNSPRT_QUIC) {
    /* QUIC sockets need to be nonblocking */
    (void)curlx_nonblock(*sockfd, TRUE);
  }

#if defined(ENABLE_IPV6) && defined(HAVE_SOCKADDR_IN6_SIN6_SCOPE_ID)
  if(conn->scope_id && (addr->family == AF_INET6)) {
    struct sockaddr_in6 * const sa6 = (void *)&addr->sa_addr;
    sa6->sin6_scope_id = conn->scope_id;
  }
#endif

  return CURLE_OK;

}