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
struct ehea_port_res {scalar_t__ sq_restart_flag; } ;
struct ehea_port {int num_def_qps; int /*<<< orphan*/  restart_wq; struct ehea_port_res* port_res; } ;

/* Variables and functions */
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_sq_restart_flag(struct ehea_port *port)
{
	int i;

	for (i = 0; i < port->num_def_qps; i++) {
		struct ehea_port_res *pr = &port->port_res[i];
		pr->sq_restart_flag = 0;
	}
	wake_up(&port->restart_wq);
}