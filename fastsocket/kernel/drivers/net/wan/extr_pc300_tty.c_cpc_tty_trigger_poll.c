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
struct TYPE_4__ {int /*<<< orphan*/  tty_tx_work; } ;
typedef  TYPE_1__ st_cpc_tty_area ;
struct TYPE_5__ {scalar_t__ cpc_tty; } ;
typedef  TYPE_2__ pc300dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

void cpc_tty_trigger_poll(pc300dev_t *pc300dev)
{
	st_cpc_tty_area *cpc_tty = (st_cpc_tty_area *)pc300dev->cpc_tty; 
	if (!cpc_tty) {
		return;
	}
	schedule_work(&(cpc_tty->tty_tx_work)); 
}