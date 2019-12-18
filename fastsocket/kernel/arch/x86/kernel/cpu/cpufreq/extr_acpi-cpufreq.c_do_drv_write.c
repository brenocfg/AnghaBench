#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int /*<<< orphan*/  bit_width; int /*<<< orphan*/  port; } ;
struct TYPE_5__ {int /*<<< orphan*/  reg; } ;
struct TYPE_6__ {TYPE_1__ io; TYPE_2__ msr; } ;
struct drv_cmd {int type; int val; TYPE_3__ addr; } ;
typedef  int /*<<< orphan*/  acpi_io_address ;

/* Variables and functions */
 int INTEL_MSR_RANGE ; 
#define  SYSTEM_INTEL_MSR_CAPABLE 129 
#define  SYSTEM_IO_CAPABLE 128 
 int /*<<< orphan*/  acpi_os_write_port (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wrmsr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void do_drv_write(void *_cmd)
{
	struct drv_cmd *cmd = _cmd;
	u32 lo, hi;

	switch (cmd->type) {
	case SYSTEM_INTEL_MSR_CAPABLE:
		rdmsr(cmd->addr.msr.reg, lo, hi);
		lo = (lo & ~INTEL_MSR_RANGE) | (cmd->val & INTEL_MSR_RANGE);
		wrmsr(cmd->addr.msr.reg, lo, hi);
		break;
	case SYSTEM_IO_CAPABLE:
		acpi_os_write_port((acpi_io_address)cmd->addr.io.port,
				cmd->val,
				(u32)cmd->addr.io.bit_width);
		break;
	default:
		break;
	}
}