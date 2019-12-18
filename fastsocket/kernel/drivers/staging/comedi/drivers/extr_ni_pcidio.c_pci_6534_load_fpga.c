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
typedef  int u8 ;
struct comedi_device {int dummy; } ;
struct TYPE_4__ {TYPE_1__* mite; } ;
struct TYPE_3__ {scalar_t__ daq_io_addr; } ;

/* Variables and functions */
 int EIO ; 
 scalar_t__ Firmware_Control_Register ; 
 scalar_t__ Firmware_Data_Register ; 
 scalar_t__ Firmware_Status_Register ; 
 TYPE_2__* devpriv ; 
 scalar_t__ need_resched () ; 
 int /*<<< orphan*/  printk (char*,int) ; 
 int readw (scalar_t__) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writew (int,scalar_t__) ; 

__attribute__((used)) static int pci_6534_load_fpga(struct comedi_device *dev, int fpga_index,
			      u8 * data, int data_len)
{
	static const int timeout = 1000;
	int i, j;
	writew(0x80 | fpga_index,
	       devpriv->mite->daq_io_addr + Firmware_Control_Register);
	writew(0xc0 | fpga_index,
	       devpriv->mite->daq_io_addr + Firmware_Control_Register);
	for (i = 0;
	     (readw(devpriv->mite->daq_io_addr +
		    Firmware_Status_Register) & 0x2) == 0 && i < timeout; ++i) {
		udelay(1);
	}
	if (i == timeout) {
		printk
		    ("ni_pcidio: failed to load fpga %i, waiting for status 0x2\n",
		     fpga_index);
		return -EIO;
	}
	writew(0x80 | fpga_index,
	       devpriv->mite->daq_io_addr + Firmware_Control_Register);
	for (i = 0;
	     readw(devpriv->mite->daq_io_addr + Firmware_Status_Register) !=
	     0x3 && i < timeout; ++i) {
		udelay(1);
	}
	if (i == timeout) {
		printk
		    ("ni_pcidio: failed to load fpga %i, waiting for status 0x3\n",
		     fpga_index);
		return -EIO;
	}
	for (j = 0; j + 1 < data_len;) {
		unsigned int value = data[j++];
		value |= data[j++] << 8;
		writew(value,
		       devpriv->mite->daq_io_addr + Firmware_Data_Register);
		for (i = 0;
		     (readw(devpriv->mite->daq_io_addr +
			    Firmware_Status_Register) & 0x2) == 0
		     && i < timeout; ++i) {
			udelay(1);
		}
		if (i == timeout) {
			printk("ni_pcidio: failed to load word into fpga %i\n",
			       fpga_index);
			return -EIO;
		}
		if (need_resched())
			schedule();
	}
	writew(0x0, devpriv->mite->daq_io_addr + Firmware_Control_Register);
	return 0;
}