#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct connectdata {int /*<<< orphan*/ * sock; TYPE_1__* handler; } ;
typedef  int /*<<< orphan*/  curl_socket_t ;
struct TYPE_2__ {int (* proto_getsock ) (struct connectdata*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 size_t FIRSTSOCKET ; 
 int GETSOCK_READSOCK (int /*<<< orphan*/ ) ; 
 int GETSOCK_WRITESOCK (int /*<<< orphan*/ ) ; 
 int stub1 (struct connectdata*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int protocol_getsock(struct connectdata *conn,
                            curl_socket_t *socks)
{
  if(conn->handler->proto_getsock)
    return conn->handler->proto_getsock(conn, socks);
  /* Backup getsock logic. Since there is a live socket in use, we must wait
     for it or it will be removed from watching when the multi_socket API is
     used. */
  socks[0] = conn->sock[FIRSTSOCKET];
  return GETSOCK_READSOCK(0) | GETSOCK_WRITESOCK(0);
}