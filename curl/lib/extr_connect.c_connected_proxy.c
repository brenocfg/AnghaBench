#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  socksproxy_connecting; scalar_t__ conn_to_port; scalar_t__ httpproxy; scalar_t__ conn_to_host; scalar_t__ socksproxy; } ;
struct TYPE_11__ {int proxytype; int /*<<< orphan*/  user; int /*<<< orphan*/  passwd; } ;
struct TYPE_7__ {char* name; } ;
struct TYPE_10__ {scalar_t__ port; TYPE_1__ host; } ;
struct TYPE_9__ {char* name; } ;
struct TYPE_8__ {char* name; } ;
struct connectdata {char* secondaryhostname; int secondary_port; int conn_to_port; int remote_port; TYPE_6__ bits; int /*<<< orphan*/  data; TYPE_5__ socks_proxy; TYPE_4__ http_proxy; TYPE_3__ host; TYPE_2__ conn_to_host; } ;
typedef  int /*<<< orphan*/  CURLcode ;

/* Variables and functions */
 int /*<<< orphan*/  CURLE_COULDNT_CONNECT ; 
 int /*<<< orphan*/  CURLE_OK ; 
#define  CURLPROXY_SOCKS4 131 
#define  CURLPROXY_SOCKS4A 130 
#define  CURLPROXY_SOCKS5 129 
#define  CURLPROXY_SOCKS5_HOSTNAME 128 
 int /*<<< orphan*/  Curl_SOCKS4 (int /*<<< orphan*/ ,char const* const,int const,int,struct connectdata*) ; 
 int /*<<< orphan*/  Curl_SOCKS5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const* const,int const,int,struct connectdata*) ; 
 int /*<<< orphan*/  FALSE ; 
 int SECONDARYSOCKET ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  failf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static CURLcode connected_proxy(struct connectdata *conn, int sockindex)
{
  CURLcode result = CURLE_OK;

  if(conn->bits.socksproxy) {
#ifndef CURL_DISABLE_PROXY
    /* for the secondary socket (FTP), use the "connect to host"
     * but ignore the "connect to port" (use the secondary port)
     */
    const char * const host = conn->bits.httpproxy ?
                              conn->http_proxy.host.name :
                              conn->bits.conn_to_host ?
                              conn->conn_to_host.name :
                              sockindex == SECONDARYSOCKET ?
                              conn->secondaryhostname : conn->host.name;
    const int port = conn->bits.httpproxy ? (int)conn->http_proxy.port :
                     sockindex == SECONDARYSOCKET ? conn->secondary_port :
                     conn->bits.conn_to_port ? conn->conn_to_port :
                     conn->remote_port;
    conn->bits.socksproxy_connecting = TRUE;
    switch(conn->socks_proxy.proxytype) {
    case CURLPROXY_SOCKS5:
    case CURLPROXY_SOCKS5_HOSTNAME:
      result = Curl_SOCKS5(conn->socks_proxy.user, conn->socks_proxy.passwd,
                         host, port, sockindex, conn);
      break;

    case CURLPROXY_SOCKS4:
    case CURLPROXY_SOCKS4A:
      result = Curl_SOCKS4(conn->socks_proxy.user, host, port, sockindex,
                           conn);
      break;

    default:
      failf(conn->data, "unknown proxytype option given");
      result = CURLE_COULDNT_CONNECT;
    } /* switch proxytype */
    conn->bits.socksproxy_connecting = FALSE;
#else
  (void)sockindex;
#endif /* CURL_DISABLE_PROXY */
  }

  return result;
}