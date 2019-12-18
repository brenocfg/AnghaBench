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
struct fc_lport {int link_up; scalar_t__ state; } ;

/* Variables and functions */
 scalar_t__ LPORT_ST_RESET ; 
 int /*<<< orphan*/  fc_lport_enter_flogi (struct fc_lport*) ; 

void __fc_linkup(struct fc_lport *lport)
{
	if (!lport->link_up) {
		lport->link_up = 1;

		if (lport->state == LPORT_ST_RESET)
			fc_lport_enter_flogi(lport);
	}
}