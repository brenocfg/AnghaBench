#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint32_t ;
struct scsi_qla_host {int /*<<< orphan*/  hardware_lock; int /*<<< orphan*/  isr_count; TYPE_2__* isp_ops; TYPE_1__* qla4_82xx_reg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  (* interrupt_service_routine ) (struct scsi_qla_host*,int) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  host_status; int /*<<< orphan*/  host_int; } ;

/* Variables and functions */
 int HSRX_RISC_IOCB_INT ; 
 int HSRX_RISC_MB_INT ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int ISRX_82XX_RISC_INT ; 
 scalar_t__ MAX_REQS_SERVICED_PER_INTR ; 
 scalar_t__ is_qla8032 (struct scsi_qla_host*) ; 
 int /*<<< orphan*/  qla4_82xx_spurious_interrupt (struct scsi_qla_host*,scalar_t__) ; 
 int /*<<< orphan*/  qla4_83xx_mailbox_intr_handler (int,void*) ; 
 int readl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (struct scsi_qla_host*,int) ; 

irqreturn_t
qla4_8xxx_default_intr_handler(int irq, void *dev_id)
{
	struct scsi_qla_host *ha = dev_id;
	unsigned long   flags;
	uint32_t intr_status;
	uint8_t reqs_count = 0;

	if (is_qla8032(ha)) {
		qla4_83xx_mailbox_intr_handler(irq, dev_id);
	} else {
		spin_lock_irqsave(&ha->hardware_lock, flags);
		while (1) {
			if (!(readl(&ha->qla4_82xx_reg->host_int) &
			    ISRX_82XX_RISC_INT)) {
				qla4_82xx_spurious_interrupt(ha, reqs_count);
				break;
			}

			intr_status =  readl(&ha->qla4_82xx_reg->host_status);
			if ((intr_status &
			    (HSRX_RISC_MB_INT | HSRX_RISC_IOCB_INT)) == 0) {
				qla4_82xx_spurious_interrupt(ha, reqs_count);
				break;
			}

			ha->isp_ops->interrupt_service_routine(ha, intr_status);

			if (++reqs_count == MAX_REQS_SERVICED_PER_INTR)
				break;
		}
		ha->isr_count++;
		spin_unlock_irqrestore(&ha->hardware_lock, flags);
	}
	return IRQ_HANDLED;
}