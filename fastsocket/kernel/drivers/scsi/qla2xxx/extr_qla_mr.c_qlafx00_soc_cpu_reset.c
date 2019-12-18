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
typedef  int uint32_t ;
struct qla_hw_data {int /*<<< orphan*/  hardware_lock; } ;
struct TYPE_3__ {struct qla_hw_data* hw; } ;
typedef  TYPE_1__ scsi_qla_host_t ;

/* Variables and functions */
 int /*<<< orphan*/  QLAFX00_SET_HBA_SOC_REG (struct qla_hw_data*,scalar_t__,int) ; 
 scalar_t__ SOC_CORE_TIMER_REG ; 
 scalar_t__ SOC_FABRIC_CONFIG_REG ; 
 scalar_t__ SOC_FABRIC_CONTROL_REG ; 
 scalar_t__ SOC_FABRIC_RST_CONTROL_REG ; 
 scalar_t__ SOC_INTERRUPT_SOURCE_I_CONTROL_REG ; 
 scalar_t__ SOC_IRQ_ACK_REG ; 
 scalar_t__ SOC_SW_RST_CONTROL_REG_CORE0 ; 
 int /*<<< orphan*/  barrier () ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void
qlafx00_soc_cpu_reset(scsi_qla_host_t *vha)
{
	unsigned long flags = 0;
	struct qla_hw_data *ha = vha->hw;
	int i, core;
	uint32_t cnt;

	/* Set all 4 cores in reset */
	for (i = 0; i < 4; i++) {
		QLAFX00_SET_HBA_SOC_REG(ha,
		    (SOC_SW_RST_CONTROL_REG_CORE0 + 8*i), (0xF01));
	}

	/* Set all 4 core Clock gating control */
	for (i = 0; i < 4; i++) {
		QLAFX00_SET_HBA_SOC_REG(ha,
		    (SOC_SW_RST_CONTROL_REG_CORE0 + 4 + 8*i), (0x01010101));
	}

	/* Reset all units in Fabric */
	QLAFX00_SET_HBA_SOC_REG(ha, SOC_FABRIC_RST_CONTROL_REG, (0x11F0101));

	/* Reset all interrupt control registers */
	for (i = 0; i < 115; i++) {
		QLAFX00_SET_HBA_SOC_REG(ha,
		    (SOC_INTERRUPT_SOURCE_I_CONTROL_REG + 4*i), (0x0));
	}

	/* Reset Timers control registers. per core */
	for (core = 0; core < 4; core++)
		for (i = 0; i < 8; i++)
			QLAFX00_SET_HBA_SOC_REG(ha,
			    (SOC_CORE_TIMER_REG + 0x100*core + 4*i), (0x0));

	/* Reset per core IRQ ack register */
	for (core = 0; core < 4; core++)
		QLAFX00_SET_HBA_SOC_REG(ha,
		    (SOC_IRQ_ACK_REG + 0x100*core), (0x3FF));

	/* Set Fabric control and config to defaults */
	QLAFX00_SET_HBA_SOC_REG(ha, SOC_FABRIC_CONTROL_REG, (0x2));
	QLAFX00_SET_HBA_SOC_REG(ha, SOC_FABRIC_CONFIG_REG, (0x3));

	spin_lock_irqsave(&ha->hardware_lock, flags);

	/* Kick in Fabric units */
	QLAFX00_SET_HBA_SOC_REG(ha, SOC_FABRIC_RST_CONTROL_REG, (0x0));

	/* Kick in Core0 to start boot process */
	QLAFX00_SET_HBA_SOC_REG(ha, SOC_SW_RST_CONTROL_REG_CORE0, (0xF00));

	/* Wait 10secs for soft-reset to complete. */
	for (cnt = 10; cnt; cnt--) {
		msleep(1000);
		barrier();
	}
	spin_unlock_irqrestore(&ha->hardware_lock, flags);
}