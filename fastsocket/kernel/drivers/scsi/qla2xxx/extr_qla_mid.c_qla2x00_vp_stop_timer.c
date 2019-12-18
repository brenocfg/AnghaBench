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
struct TYPE_3__ {scalar_t__ timer_active; int /*<<< orphan*/  timer; scalar_t__ vp_idx; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 

void
qla2x00_vp_stop_timer(scsi_qla_host_t *vha)
{
	if (vha->vp_idx && vha->timer_active) {
		del_timer_sync(&vha->timer);
		vha->timer_active = 0;
	}
}