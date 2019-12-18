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
struct connectdata {scalar_t__ connect_state; int /*<<< orphan*/ * sock; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;

/* Variables and functions */
 size_t FIRSTSOCKET ; 
 int GETSOCK_READSOCK (int /*<<< orphan*/ ) ; 
 int GETSOCK_WRITESOCK (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int waitproxyconnect_getsock(struct connectdata *conn,
                                    curl_socket_t *sock)
{
  sock[0] = conn->sock[FIRSTSOCKET];

  /* when we've sent a CONNECT to a proxy, we should rather wait for the
     socket to become readable to be able to get the response headers */
  if(conn->connect_state)
    return GETSOCK_READSOCK(0);

  return GETSOCK_WRITESOCK(0);
}