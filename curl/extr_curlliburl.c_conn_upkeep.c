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
struct connectdata {TYPE_1__* handler; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* connection_check ) (struct connectdata*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CONNCHECK_KEEPALIVE ; 
 int /*<<< orphan*/  stub1 (struct connectdata*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int conn_upkeep(struct connectdata *conn,
                       void *param)
{
  /* Param is unused. */
  (void)param;

  if(conn->handler->connection_check) {
    /* Do a protocol-specific keepalive check on the connection. */
    conn->handler->connection_check(conn, CONNCHECK_KEEPALIVE);
  }

  return 0; /* continue iteration */
}