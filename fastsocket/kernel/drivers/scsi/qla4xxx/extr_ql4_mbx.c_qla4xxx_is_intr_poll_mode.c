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
struct scsi_qla_host {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_83XX_MBOX_INTR_ON ; 
 int /*<<< orphan*/  AF_HA_REMOVAL ; 
 int /*<<< orphan*/  AF_INTERRUPTS_ON ; 
 int /*<<< orphan*/  AF_IRQ_ATTACHED ; 
 int /*<<< orphan*/  AF_ONLINE ; 
 scalar_t__ is_qla8032 (struct scsi_qla_host*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int qla4xxx_is_intr_poll_mode(struct scsi_qla_host *ha)
{
	int rval = 1;

	if (is_qla8032(ha)) {
		if (test_bit(AF_IRQ_ATTACHED, &ha->flags) &&
		    test_bit(AF_83XX_MBOX_INTR_ON, &ha->flags))
			rval = 0;
	} else {
		if (test_bit(AF_IRQ_ATTACHED, &ha->flags) &&
		    test_bit(AF_INTERRUPTS_ON, &ha->flags) &&
		    test_bit(AF_ONLINE, &ha->flags) &&
		    !test_bit(AF_HA_REMOVAL, &ha->flags))
			rval = 0;
	}

	return rval;
}