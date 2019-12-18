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
struct saa7164_fw_status {void* remainheap; void* cpuload; void* inst; void* spec; void* mode; void* status; } ;
struct saa7164_dev {struct saa7164_fw_status fw_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAA_DEVICE_SYSINIT_CPULOAD ; 
 int /*<<< orphan*/  SAA_DEVICE_SYSINIT_INST ; 
 int /*<<< orphan*/  SAA_DEVICE_SYSINIT_MODE ; 
 int /*<<< orphan*/  SAA_DEVICE_SYSINIT_REMAINHEAP ; 
 int /*<<< orphan*/  SAA_DEVICE_SYSINIT_SPEC ; 
 int /*<<< orphan*/  SAA_DEVICE_SYSINIT_STATUS ; 
 int /*<<< orphan*/  dprintk (int,char*,...) ; 
 void* saa7164_readl (int /*<<< orphan*/ ) ; 

void saa7164_getfirmwarestatus(struct saa7164_dev *dev)
{
	struct saa7164_fw_status *s = &dev->fw_status;

	dev->fw_status.status = saa7164_readl(SAA_DEVICE_SYSINIT_STATUS);
	dev->fw_status.mode = saa7164_readl(SAA_DEVICE_SYSINIT_MODE);
	dev->fw_status.spec = saa7164_readl(SAA_DEVICE_SYSINIT_SPEC);
	dev->fw_status.inst = saa7164_readl(SAA_DEVICE_SYSINIT_INST);
	dev->fw_status.cpuload = saa7164_readl(SAA_DEVICE_SYSINIT_CPULOAD);
	dev->fw_status.remainheap =
		saa7164_readl(SAA_DEVICE_SYSINIT_REMAINHEAP);

	dprintk(1, "Firmware status:\n");
	dprintk(1, " .status     = 0x%08x\n", s->status);
	dprintk(1, " .mode       = 0x%08x\n", s->mode);
	dprintk(1, " .spec       = 0x%08x\n", s->spec);
	dprintk(1, " .inst       = 0x%08x\n", s->inst);
	dprintk(1, " .cpuload    = 0x%08x\n", s->cpuload);
	dprintk(1, " .remainheap = 0x%08x\n", s->remainheap);
}