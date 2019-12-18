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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
#define  MSG_HEAD_TAG 130 
#define  MSG_ORDERED_TAG 129 
#define  MSG_SIMPLE_TAG 128 
 int /*<<< orphan*/  TASK_TAG_ORDERED ; 
 int /*<<< orphan*/  TASK_TAG_QUEUE_HEAD ; 
 int /*<<< orphan*/  TASK_TAG_SIMPLE ; 
 scalar_t__ scsi_populate_tag_msg (struct scsi_cmnd*,char*) ; 

__attribute__((used)) static u8 pmcraid_task_attributes(struct scsi_cmnd *scsi_cmd)
{
	char tag[2];
	u8 rc = 0;

	if (scsi_populate_tag_msg(scsi_cmd, tag)) {
		switch (tag[0]) {
		case MSG_SIMPLE_TAG:
			rc = TASK_TAG_SIMPLE;
			break;
		case MSG_HEAD_TAG:
			rc = TASK_TAG_QUEUE_HEAD;
			break;
		case MSG_ORDERED_TAG:
			rc = TASK_TAG_ORDERED;
			break;
		};
	}

	return rc;
}