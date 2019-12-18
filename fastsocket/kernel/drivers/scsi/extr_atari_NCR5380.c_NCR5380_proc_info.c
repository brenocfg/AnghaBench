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
struct Scsi_Host {scalar_t__ hostdata; } ;
struct NCR5380_hostdata {scalar_t__ disconnected_queue; scalar_t__ issue_queue; scalar_t__ connected; } ;
typedef  long off_t ;
typedef  int /*<<< orphan*/  Scsi_Cmnd ;

/* Variables and functions */
 int ENOSYS ; 
 char* HOSTNO ; 
 char* NCR5380_PUBLIC_RELEASE ; 
 int /*<<< orphan*/ * NEXT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SPRINTF (char*,char*) ; 
 int /*<<< orphan*/  check_offset () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 char* lprint_Scsi_Cmnd (int /*<<< orphan*/ *,char*,char*,int) ; 
 scalar_t__ main_running ; 

__attribute__((used)) static int NCR5380_proc_info(struct Scsi_Host *instance, char *buffer,
			     char **start, off_t offset, int length, int inout)
{
	char *pos = buffer;
	struct NCR5380_hostdata *hostdata;
	Scsi_Cmnd *ptr;
	unsigned long flags;
	off_t begin = 0;
#define check_offset()					\
	do {						\
		if (pos - buffer < offset - begin) {	\
			begin += pos - buffer;		\
			pos = buffer;			\
		}					\
	} while (0)

	hostdata = (struct NCR5380_hostdata *)instance->hostdata;

	if (inout)			/* Has data been written to the file ? */
		return -ENOSYS;		/* Currently this is a no-op */
	SPRINTF("NCR5380 core release=%d.\n", NCR5380_PUBLIC_RELEASE);
	check_offset();
	local_irq_save(flags);
	SPRINTF("NCR5380: coroutine is%s running.\n",
		main_running ? "" : "n't");
	check_offset();
	if (!hostdata->connected)
		SPRINTF("scsi%d: no currently connected command\n", HOSTNO);
	else
		pos = lprint_Scsi_Cmnd((Scsi_Cmnd *) hostdata->connected,
				       pos, buffer, length);
	SPRINTF("scsi%d: issue_queue\n", HOSTNO);
	check_offset();
	for (ptr = (Scsi_Cmnd *)hostdata->issue_queue; ptr; ptr = NEXT(ptr)) {
		pos = lprint_Scsi_Cmnd(ptr, pos, buffer, length);
		check_offset();
	}

	SPRINTF("scsi%d: disconnected_queue\n", HOSTNO);
	check_offset();
	for (ptr = (Scsi_Cmnd *) hostdata->disconnected_queue; ptr;
	     ptr = NEXT(ptr)) {
		pos = lprint_Scsi_Cmnd(ptr, pos, buffer, length);
		check_offset();
	}

	local_irq_restore(flags);
	*start = buffer + (offset - begin);
	if (pos - buffer < offset - begin)
		return 0;
	else if (pos - buffer - (offset - begin) < length)
		return pos - buffer - (offset - begin);
	return length;
}