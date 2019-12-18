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
struct Scsi_Host {int dummy; } ;
struct TYPE_2__ {int slot; int interrupt; int port_address; int dma_channel; scalar_t__ bios_segment; scalar_t__ subversion; } ;

/* Variables and functions */
 TYPE_1__ config ; 
 int /*<<< orphan*/  sprintf (char*,char*,int,int,...) ; 

__attribute__((used)) static const char *ultrastor_info(struct Scsi_Host * shpnt)
{
    static char buf[64];

    if (config.slot)
      sprintf(buf, "UltraStor 24F SCSI @ Slot %u IRQ%u",
	      config.slot, config.interrupt);
    else if (config.subversion)
      sprintf(buf, "UltraStor 34F SCSI @ Port %03X BIOS %05X IRQ%u",
	      config.port_address, (int)config.bios_segment,
	      config.interrupt);
    else
      sprintf(buf, "UltraStor 14F SCSI @ Port %03X BIOS %05X IRQ%u DMA%u",
	      config.port_address, (int)config.bios_segment,
	      config.interrupt, config.dma_channel);
    return buf;
}