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
struct scsi_cmnd {int dummy; } ;

/* Variables and functions */
 int FAILED ; 
 int iscsi_eh_session_reset (struct scsi_cmnd*) ; 
 int iscsi_eh_target_reset (struct scsi_cmnd*) ; 

int iscsi_eh_recover_target(struct scsi_cmnd *sc)
{
	int rc;

	rc = iscsi_eh_target_reset(sc);
	if (rc == FAILED)
		rc = iscsi_eh_session_reset(sc);
	return rc;
}