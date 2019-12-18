#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int nat_traversal_task_oustanding; int /*<<< orphan*/  tcp_port; int /*<<< orphan*/  nat_traversal_state; } ;
typedef  TYPE_1__ netplay_t ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  task_push_netplay_nat_traversal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void netplay_init_nat_traversal(netplay_t *netplay)
{
   memset(&netplay->nat_traversal_state, 0, sizeof(netplay->nat_traversal_state));
   netplay->nat_traversal_task_oustanding = true;
   task_push_netplay_nat_traversal(&netplay->nat_traversal_state, netplay->tcp_port);
}