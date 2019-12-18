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
struct Scsi_Host {int host_no; unsigned int io_port; int this_id; int /*<<< orphan*/  sg_tablesize; int /*<<< orphan*/  base; scalar_t__ n_io_port; int /*<<< orphan*/  irq; scalar_t__ hostdata; } ;
typedef  int off_t ;
struct TYPE_5__ {TYPE_3__* target; int /*<<< orphan*/  Lock; int /*<<< orphan*/  CurrentSC; TYPE_1__* pci_devid; scalar_t__ MmioLength; } ;
typedef  TYPE_2__ nsp32_hw_data ;
struct TYPE_6__ {scalar_t__ sync_flag; int period; scalar_t__ offset; } ;
struct TYPE_4__ {long driver_data; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_3__*) ; 
 scalar_t__ ASYNC_OFFSET ; 
 int /*<<< orphan*/  CHIP_MODE ; 
 int EINVAL ; 
 int /*<<< orphan*/  INDEX_REG ; 
 unsigned char OEM0 ; 
 unsigned char OEM1 ; 
 unsigned char OPTF ; 
 scalar_t__ SDTR_DONE ; 
 int /*<<< orphan*/  SPRINTF (char*,...) ; 
 int TRUE ; 
 int min (int,int) ; 
 unsigned char nsp32_index_read1 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * nsp32_model ; 
 int nsp32_read2 (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nsp32_release_version ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int nsp32_proc_info(struct Scsi_Host *host, char *buffer, char **start,
			   off_t offset, int length, int inout)
{
	char             *pos = buffer;
	int               thislength;
	unsigned long     flags;
	nsp32_hw_data    *data;
	int               hostno;
	unsigned int      base;
	unsigned char     mode_reg;
	int               id, speed;
	long              model;

	/* Write is not supported, just return. */
	if (inout == TRUE) {
		return -EINVAL;
	}

	hostno = host->host_no;
	data = (nsp32_hw_data *)host->hostdata;
	base = host->io_port;

	SPRINTF("NinjaSCSI-32 status\n\n");
	SPRINTF("Driver version:        %s, $Revision: 1.33 $\n", nsp32_release_version);
	SPRINTF("SCSI host No.:         %d\n",		hostno);
	SPRINTF("IRQ:                   %d\n",		host->irq);
	SPRINTF("IO:                    0x%lx-0x%lx\n", host->io_port, host->io_port + host->n_io_port - 1);
	SPRINTF("MMIO(virtual address): 0x%lx-0x%lx\n",	host->base, host->base + data->MmioLength - 1);
	SPRINTF("sg_tablesize:          %d\n",		host->sg_tablesize);
	SPRINTF("Chip revision:         0x%x\n",       	(nsp32_read2(base, INDEX_REG) >> 8) & 0xff);

	mode_reg = nsp32_index_read1(base, CHIP_MODE);
	model    = data->pci_devid->driver_data;

#ifdef CONFIG_PM
	SPRINTF("Power Management:      %s\n",          (mode_reg & OPTF) ? "yes" : "no");
#endif
	SPRINTF("OEM:                   %ld, %s\n",     (mode_reg & (OEM0|OEM1)), nsp32_model[model]);

	spin_lock_irqsave(&(data->Lock), flags);
	SPRINTF("CurrentSC:             0x%p\n\n",      data->CurrentSC);
	spin_unlock_irqrestore(&(data->Lock), flags);


	SPRINTF("SDTR status\n");
	for (id = 0; id < ARRAY_SIZE(data->target); id++) {

                SPRINTF("id %d: ", id);

		if (id == host->this_id) {
			SPRINTF("----- NinjaSCSI-32 host adapter\n");
			continue;
		}

		if (data->target[id].sync_flag == SDTR_DONE) {
			if (data->target[id].period == 0            &&
			    data->target[id].offset == ASYNC_OFFSET ) {
				SPRINTF("async");
			} else {
				SPRINTF(" sync");
			}
		} else {
			SPRINTF(" none");
		}

		if (data->target[id].period != 0) {

			speed = 1000000 / (data->target[id].period * 4);

			SPRINTF(" transfer %d.%dMB/s, offset %d",
				speed / 1000,
				speed % 1000,
				data->target[id].offset
				);
		}
		SPRINTF("\n");
	}


	thislength = pos - (buffer + offset);

	if(thislength < 0) {
		*start = NULL;
                return 0;
        }


	thislength = min(thislength, length);
	*start = buffer + offset;

	return thislength;
}