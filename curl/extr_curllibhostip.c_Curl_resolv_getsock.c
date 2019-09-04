#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct connectdata {int dummy; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 int GETSOCK_BLANK ; 

int Curl_resolv_getsock(struct connectdata *conn,
                        curl_socket_t *socks,
                        int numsocks)
{
#ifdef CURLRES_ASYNCH
  if(conn->data->set.doh)
    /* nothing to wait for during DOH resolve, those handles have their own
       sockets */
    return GETSOCK_BLANK;
  return Curl_resolver_getsock(conn, socks, numsocks);
#else
  (void)conn;
  (void)socks;
  (void)numsocks;
  return GETSOCK_BLANK;
#endif
}