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
struct TYPE_5__ {int /*<<< orphan*/  goodbye_watcher; TYPE_1__* server; } ;
typedef  TYPE_2__ ebb_connection ;
struct TYPE_4__ {int /*<<< orphan*/  loop; } ;

/* Variables and functions */
 int /*<<< orphan*/  ev_timer_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void 
ebb_connection_schedule_close(ebb_connection *connection)
{
  ev_timer_start(connection->server->loop, &connection->goodbye_watcher);
}