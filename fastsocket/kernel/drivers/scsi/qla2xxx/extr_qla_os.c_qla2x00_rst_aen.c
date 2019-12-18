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
struct TYPE_4__ {int /*<<< orphan*/  reset_active; scalar_t__ online; } ;
struct TYPE_5__ {int marker_needed; int /*<<< orphan*/  dpc_flags; int /*<<< orphan*/  loop_down_timer; TYPE_1__ flags; } ;
typedef  TYPE_2__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  ABORT_ISP_ACTIVE ; 
 int /*<<< orphan*/  RESET_MARKER_NEEDED ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla2x00_rst_aen(scsi_qla_host_t *vha)
{
	if (vha->flags.online && !vha->flags.reset_active &&
	    !atomic_read(&vha->loop_down_timer) &&
	    !(test_bit(ABORT_ISP_ACTIVE, &vha->dpc_flags))) {
		do {
			clear_bit(RESET_MARKER_NEEDED, &vha->dpc_flags);

			/*
			 * Issue marker command only when we are going to start
			 * the I/O.
			 */
			vha->marker_needed = 1;
		} while (!atomic_read(&vha->loop_down_timer) &&
		    (test_bit(RESET_MARKER_NEEDED, &vha->dpc_flags)));
	}
}