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
struct TYPE_4__ {int /*<<< orphan*/  close; int /*<<< orphan*/ * proxy_ssl_connected; } ;
struct TYPE_3__ {scalar_t__ proxytype; } ;
struct connectdata {TYPE_2__ bits; TYPE_1__ http_proxy; } ;
typedef  scalar_t__ CURLcode ;

/* Variables and functions */
 scalar_t__ CURLE_NOT_BUILT_IN ; 
 scalar_t__ CURLE_OK ; 
 scalar_t__ CURLPROXY_HTTPS ; 
 scalar_t__ Curl_ssl_connect_nonblocking (struct connectdata*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DEBUGASSERT (int) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static CURLcode https_proxy_connect(struct connectdata *conn, int sockindex)
{
#ifdef USE_SSL
  CURLcode result = CURLE_OK;
  DEBUGASSERT(conn->http_proxy.proxytype == CURLPROXY_HTTPS);
  if(!conn->bits.proxy_ssl_connected[sockindex]) {
    /* perform SSL initialization for this socket */
    result =
      Curl_ssl_connect_nonblocking(conn, sockindex,
                                   &conn->bits.proxy_ssl_connected[sockindex]);
    if(result)
      conn->bits.close = TRUE; /* a failed connection is marked for closure to
                                  prevent (bad) re-use or similar */
  }
  return result;
#else
  (void) conn;
  (void) sockindex;
  return CURLE_NOT_BUILT_IN;
#endif
}