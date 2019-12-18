#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int phase; int /*<<< orphan*/  buffers_residual; int /*<<< orphan*/  this_residual; } ;
struct TYPE_9__ {TYPE_2__ SCp; int /*<<< orphan*/ * cmnd; TYPE_1__* device; } ;
struct TYPE_7__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; } ;
typedef  TYPE_3__ Scsi_Cmnd ;

/* Variables and functions */
 int COMMAND_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCNEXT (TYPE_3__*) ; 
 int /*<<< orphan*/  SPRINTF (char*,...) ; 
 int aborted ; 
 int completed ; 
 int disconnected ; 
 int identified ; 
 int not_issued ; 
 int /*<<< orphan*/  scsi_get_resid (TYPE_3__*) ; 
 int selecting ; 
 int spiordy ; 
 int syncneg ; 

__attribute__((used)) static int get_command(char *pos, Scsi_Cmnd * ptr)
{
	char *start = pos;
	int i;

	SPRINTF("0x%08x: target=%d; lun=%d; cmnd=( ",
		(unsigned int) ptr, ptr->device->id, ptr->device->lun);

	for (i = 0; i < COMMAND_SIZE(ptr->cmnd[0]); i++)
		SPRINTF("0x%02x ", ptr->cmnd[i]);

	SPRINTF("); resid=%d; residual=%d; buffers=%d; phase |",
		scsi_get_resid(ptr), ptr->SCp.this_residual,
		ptr->SCp.buffers_residual);

	if (ptr->SCp.phase & not_issued)
		SPRINTF("not issued|");
	if (ptr->SCp.phase & selecting)
		SPRINTF("selecting|");
	if (ptr->SCp.phase & disconnected)
		SPRINTF("disconnected|");
	if (ptr->SCp.phase & aborted)
		SPRINTF("aborted|");
	if (ptr->SCp.phase & identified)
		SPRINTF("identified|");
	if (ptr->SCp.phase & completed)
		SPRINTF("completed|");
	if (ptr->SCp.phase & spiordy)
		SPRINTF("spiordy|");
	if (ptr->SCp.phase & syncneg)
		SPRINTF("syncneg|");
	SPRINTF("; next=0x%p\n", SCNEXT(ptr));

	return (pos - start);
}