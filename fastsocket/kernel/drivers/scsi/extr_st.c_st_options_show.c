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
struct st_modedef {scalar_t__ sysv; scalar_t__ defaults_for_writes; scalar_t__ do_read_ahead; scalar_t__ do_async_writes; scalar_t__ do_buffer_writes; } ;
struct scsi_tape {scalar_t__ sili; scalar_t__ immediate; scalar_t__ scsi2_logical; scalar_t__ can_partitions; scalar_t__ omit_blklims; scalar_t__ can_bsr; scalar_t__ fast_mteom; scalar_t__ two_fm; struct st_modedef* modes; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  DEB (int) ; 
 int MT_ST_ASYNC_WRITES ; 
 int MT_ST_BUFFER_WRITES ; 
 int MT_ST_CAN_BSR ; 
 int MT_ST_CAN_PARTITIONS ; 
 int MT_ST_DEBUGGING ; 
 int MT_ST_DEF_WRITES ; 
 int MT_ST_FAST_MTEOM ; 
 int MT_ST_NOWAIT ; 
 int MT_ST_NO_BLKLIMS ; 
 int MT_ST_READ_AHEAD ; 
 int MT_ST_SCSI2LOGICAL ; 
 int MT_ST_SILI ; 
 int MT_ST_SYSV ; 
 int MT_ST_TWO_FM ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int ST_NBR_MODES ; 
 scalar_t__ debugging ; 
 struct st_modedef* dev_get_drvdata (struct device*) ; 
 struct scsi_tape** scsi_tapes ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int st_dev_max ; 

__attribute__((used)) static ssize_t
st_options_show(struct device *dev, struct device_attribute *attr, char *buf)
{
	struct st_modedef *STm = dev_get_drvdata(dev);
	struct scsi_tape *STp;
	int i, j, options;
	ssize_t l = 0;

	for (i=0; i < st_dev_max; i++) {
		for (j=0; j < ST_NBR_MODES; j++)
			if (&scsi_tapes[i]->modes[j] == STm)
				break;
		if (j < ST_NBR_MODES)
			break;
	}
	if (i == st_dev_max)
		return 0;  /* should never happen */

	STp = scsi_tapes[i];

	options = STm->do_buffer_writes ? MT_ST_BUFFER_WRITES : 0;
	options |= STm->do_async_writes ? MT_ST_ASYNC_WRITES : 0;
	options |= STm->do_read_ahead ? MT_ST_READ_AHEAD : 0;
	DEB( options |= debugging ? MT_ST_DEBUGGING : 0 );
	options |= STp->two_fm ? MT_ST_TWO_FM : 0;
	options |= STp->fast_mteom ? MT_ST_FAST_MTEOM : 0;
	options |= STm->defaults_for_writes ? MT_ST_DEF_WRITES : 0;
	options |= STp->can_bsr ? MT_ST_CAN_BSR : 0;
	options |= STp->omit_blklims ? MT_ST_NO_BLKLIMS : 0;
	options |= STp->can_partitions ? MT_ST_CAN_PARTITIONS : 0;
	options |= STp->scsi2_logical ? MT_ST_SCSI2LOGICAL : 0;
	options |= STm->sysv ? MT_ST_SYSV : 0;
	options |= STp->immediate ? MT_ST_NOWAIT : 0;
	options |= STp->sili ? MT_ST_SILI : 0;

	l = snprintf(buf, PAGE_SIZE, "0x%08x\n", options);
	return l;
}