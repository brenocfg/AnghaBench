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
typedef  int u8 ;
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int IPR_FLAGS_LO_HEAD_OF_Q_TASK ; 
 int IPR_FLAGS_LO_ORDERED_TASK ; 
 int IPR_FLAGS_LO_SIMPLE_TASK ; 
 int IPR_FLAGS_LO_UNTAGGED_TASK ; 
#define  MSG_HEAD_TAG 130 
#define  MSG_ORDERED_TAG 129 
#define  MSG_SIMPLE_TAG 128 
 scalar_t__ scsi_populate_tag_msg (struct scsi_cmnd*,int*) ; 

__attribute__((used)) static u8 ipr_get_task_attributes(struct scsi_cmnd *scsi_cmd)
{
	u8 tag[2];
	u8 rc = IPR_FLAGS_LO_UNTAGGED_TASK;

	if (scsi_populate_tag_msg(scsi_cmd, tag)) {
		switch (tag[0]) {
		case MSG_SIMPLE_TAG:
			rc = IPR_FLAGS_LO_SIMPLE_TASK;
			break;
		case MSG_HEAD_TAG:
			rc = IPR_FLAGS_LO_HEAD_OF_Q_TASK;
			break;
		case MSG_ORDERED_TAG:
			rc = IPR_FLAGS_LO_ORDERED_TASK;
			break;
		};
	}

	return rc;
}