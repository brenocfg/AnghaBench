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
struct pingpong {scalar_t__ sendleft; struct connectdata* conn; } ;
struct connectdata {int /*<<< orphan*/ * sock; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 size_t FIRSTSOCKET ; 
 int GETSOCK_READSOCK (int /*<<< orphan*/ ) ; 
 int GETSOCK_WRITESOCK (int /*<<< orphan*/ ) ; 

int Curl_pp_getsock(struct pingpong *pp,
                    curl_socket_t *socks)
{
  struct connectdata *conn = pp->conn;
  socks[0] = conn->sock[FIRSTSOCKET];

  if(pp->sendleft) {
    /* write mode */
    return GETSOCK_WRITESOCK(0);
  }

  /* read mode */
  return GETSOCK_READSOCK(0);
}