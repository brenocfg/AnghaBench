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
struct scsi_cmnd {int result; int /*<<< orphan*/  (* scsi_done ) (struct scsi_cmnd*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct scsi_cmnd*) ; 

__attribute__((used)) static inline void acornscsi_reportstatus(struct scsi_cmnd **SCpntp1,
					  struct scsi_cmnd **SCpntp2,
					  int result)
{
	struct scsi_cmnd *SCpnt = *SCpntp1;

    if (SCpnt) {
	*SCpntp1 = NULL;

	SCpnt->result = result;
	SCpnt->scsi_done(SCpnt);
    }

    if (SCpnt == *SCpntp2)
	*SCpntp2 = NULL;
}