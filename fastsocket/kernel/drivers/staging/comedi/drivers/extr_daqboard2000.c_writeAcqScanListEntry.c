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
typedef  int u16 ;
struct daqboard2000_hw {int acqScanListFIFO; } ;
struct comedi_device {int dummy; } ;
struct TYPE_2__ {struct daqboard2000_hw* daq; } ;

/* Variables and functions */
 TYPE_1__* devpriv ; 

__attribute__((used)) static void writeAcqScanListEntry(struct comedi_device *dev, u16 entry)
{
	struct daqboard2000_hw *fpga = devpriv->daq;

/* udelay(4); */
	fpga->acqScanListFIFO = entry & 0x00ff;
/* udelay(4); */
	fpga->acqScanListFIFO = (entry >> 8) & 0x00ff;
}