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
struct aha1740_hostdata {scalar_t__ translation; TYPE_1__* edev; } ;
struct Scsi_Host {char* io_port; int /*<<< orphan*/  irq; } ;
typedef  int off_t ;
struct TYPE_2__ {int /*<<< orphan*/  slot; } ;

/* Variables and functions */
 int ENOSYS ; 
 struct aha1740_hostdata* HOSTDATA (struct Scsi_Host*) ; 
 int sprintf (char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int aha1740_proc_info(struct Scsi_Host *shpnt, char *buffer,
			     char **start, off_t offset,
			     int length, int inout)
{
	int len;
	struct aha1740_hostdata *host;

	if (inout)
		return-ENOSYS;

	host = HOSTDATA(shpnt);

	len = sprintf(buffer, "aha174x at IO:%lx, IRQ %d, SLOT %d.\n"
		      "Extended translation %sabled.\n",
		      shpnt->io_port, shpnt->irq, host->edev->slot,
		      host->translation ? "en" : "dis");

	if (offset > len) {
		*start = buffer;
		return 0;
	}

	*start = buffer + offset;
	len -= offset;
	if (len > length)
		len = length;
	return len;
}