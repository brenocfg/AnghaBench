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
struct connectdata {TYPE_2__* data; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;
struct TYPE_3__ {scalar_t__ doh; } ;
struct TYPE_4__ {TYPE_1__ set; } ;

/* Variables and functions */
 int Curl_resolver_getsock (struct connectdata*,int /*<<< orphan*/ *) ; 
 int GETSOCK_BLANK ; 

int Curl_resolv_getsock(struct connectdata *conn,
                        curl_socket_t *socks)
{
#ifdef CURLRES_ASYNCH
  if(conn->data->set.doh)
    /* nothing to wait for during DOH resolve, those handles have their own
       sockets */
    return GETSOCK_BLANK;
  return Curl_resolver_getsock(conn, socks);
#else
  (void)conn;
  (void)socks;
  return GETSOCK_BLANK;
#endif
}