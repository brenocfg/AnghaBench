#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  do_more; } ;
struct connectdata {scalar_t__* sock; int /*<<< orphan*/ * sock_accepted; TYPE_1__ bits; struct Curl_easy* data; } ;
struct Curl_sockaddr_storage {int dummy; } ;
struct TYPE_4__ {int (* fsockopt ) (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sockopt_client; } ;
struct Curl_easy {TYPE_2__ set; } ;
typedef  int curl_socklen_t ;
typedef  scalar_t__ curl_socket_t ;
typedef  int /*<<< orphan*/  add ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_ABORTED_BY_CALLBACK ; 
 int /*<<< orphan*/  CURLE_FTP_PORT_FAILED ; 
 int /*<<< orphan*/  CURLE_OK ; 
 int /*<<< orphan*/  CURLSOCKTYPE_ACCEPT ; 
 scalar_t__ CURL_SOCKET_BAD ; 
 int /*<<< orphan*/  Curl_closesocket (struct connectdata*,scalar_t__) ; 
 int /*<<< orphan*/  Curl_set_in_callback (struct Curl_easy*,int) ; 
 int /*<<< orphan*/  FALSE ; 
 size_t SECONDARYSOCKET ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ accept (scalar_t__,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close_secondarysocket (struct connectdata*) ; 
 int /*<<< orphan*/  curlx_nonblock (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  failf (struct Curl_easy*,char*) ; 
 scalar_t__ getsockname (scalar_t__,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  infof (struct Curl_easy*,char*) ; 
 int stub1 (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static CURLcode AcceptServerConnect(struct connectdata *conn)
{
  struct Curl_easy *data = conn->data;
  curl_socket_t sock = conn->sock[SECONDARYSOCKET];
  curl_socket_t s = CURL_SOCKET_BAD;
#ifdef ENABLE_IPV6
  struct Curl_sockaddr_storage add;
#else
  struct sockaddr_in add;
#endif
  curl_socklen_t size = (curl_socklen_t) sizeof(add);

  if(0 == getsockname(sock, (struct sockaddr *) &add, &size)) {
    size = sizeof(add);

    s = accept(sock, (struct sockaddr *) &add, &size);
  }
  Curl_closesocket(conn, sock); /* close the first socket */

  if(CURL_SOCKET_BAD == s) {
    failf(data, "Error accept()ing server connect");
    return CURLE_FTP_PORT_FAILED;
  }
  infof(data, "Connection accepted from server\n");
  /* when this happens within the DO state it is important that we mark us as
     not needing DO_MORE anymore */
  conn->bits.do_more = FALSE;

  conn->sock[SECONDARYSOCKET] = s;
  (void)curlx_nonblock(s, TRUE); /* enable non-blocking */
  conn->sock_accepted[SECONDARYSOCKET] = TRUE;

  if(data->set.fsockopt) {
    int error = 0;

    /* activate callback for setting socket options */
    Curl_set_in_callback(data, true);
    error = data->set.fsockopt(data->set.sockopt_client,
                               s,
                               CURLSOCKTYPE_ACCEPT);
    Curl_set_in_callback(data, false);

    if(error) {
      close_secondarysocket(conn);
      return CURLE_ABORTED_BY_CALLBACK;
    }
  }

  return CURLE_OK;

}