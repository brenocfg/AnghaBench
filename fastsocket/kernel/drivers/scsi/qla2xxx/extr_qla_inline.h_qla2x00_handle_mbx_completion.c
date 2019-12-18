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
struct TYPE_2__ {scalar_t__ mbox_int; } ;
struct qla_hw_data {int /*<<< orphan*/  mbx_intr_comp; int /*<<< orphan*/  mbx_cmd_flags; TYPE_1__ flags; } ;

/* Variables and functions */
 int MBX_INTERRUPT ; 
 int /*<<< orphan*/  MBX_INTR_WAIT ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
qla2x00_handle_mbx_completion(struct qla_hw_data *ha, int status)
{
	if (test_bit(MBX_INTR_WAIT, &ha->mbx_cmd_flags) &&
	    (status & MBX_INTERRUPT) && ha->flags.mbox_int) {
		set_bit(MBX_INTERRUPT, &ha->mbx_cmd_flags);
		clear_bit(MBX_INTR_WAIT, &ha->mbx_cmd_flags);
		complete(&ha->mbx_intr_comp);
	}
}