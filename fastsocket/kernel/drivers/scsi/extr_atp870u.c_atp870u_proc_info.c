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
typedef  int /*<<< orphan*/  u8 ;
struct Scsi_Host {int io_port; int irq; } ;
typedef  scalar_t__ off_t ;
typedef  int /*<<< orphan*/  buff ;

/* Variables and functions */
 int /*<<< orphan*/  BLS ; 
 int EINVAL ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sprintf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int atp870u_proc_info(struct Scsi_Host *HBAptr, char *buffer, 
			     char **start, off_t offset, int length, int inout)
{
	static u8 buff[512];
	int size = 0;
	int len = 0;
	off_t begin = 0;
	off_t pos = 0;
	
	if (inout) 	
		return -EINVAL;
	if (offset == 0)
		memset(buff, 0, sizeof(buff));
	size += sprintf(BLS, "ACARD AEC-671X Driver Version: 2.6+ac\n");
	len += size;
	pos = begin + len;
	size = 0;

	size += sprintf(BLS, "\n");
	size += sprintf(BLS, "Adapter Configuration:\n");
	size += sprintf(BLS, "               Base IO: %#.4lx\n", HBAptr->io_port);
	size += sprintf(BLS, "                   IRQ: %d\n", HBAptr->irq);
	len += size;
	pos = begin + len;
	
	*start = buffer + (offset - begin);	/* Start of wanted data */
	len -= (offset - begin);	/* Start slop */
	if (len > length) {
		len = length;	/* Ending slop */
	}
	return (len);
}