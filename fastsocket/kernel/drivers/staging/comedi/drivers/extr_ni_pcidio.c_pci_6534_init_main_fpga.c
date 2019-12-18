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
struct comedi_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mite; } ;
struct TYPE_3__ {scalar_t__ daq_io_addr; } ;

/* Variables and functions */
 scalar_t__ FPGA_Control1_Register ; 
 scalar_t__ FPGA_Control2_Register ; 
 scalar_t__ FPGA_SCALS_Counter_Register ; 
 scalar_t__ FPGA_SCAMS_Counter_Register ; 
 scalar_t__ FPGA_SCBLS_Counter_Register ; 
 scalar_t__ FPGA_SCBMS_Counter_Register ; 
 TYPE_2__* devpriv ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void pci_6534_init_main_fpga(struct comedi_device *dev)
{
	writel(0, devpriv->mite->daq_io_addr + FPGA_Control1_Register);
	writel(0, devpriv->mite->daq_io_addr + FPGA_Control2_Register);
	writel(0, devpriv->mite->daq_io_addr + FPGA_SCALS_Counter_Register);
	writel(0, devpriv->mite->daq_io_addr + FPGA_SCAMS_Counter_Register);
	writel(0, devpriv->mite->daq_io_addr + FPGA_SCBLS_Counter_Register);
	writel(0, devpriv->mite->daq_io_addr + FPGA_SCBMS_Counter_Register);
}