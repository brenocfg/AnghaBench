#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__* cmnd; scalar_t__ result; } ;
typedef  TYPE_1__ Scsi_Cmnd ;

/* Variables and functions */
 scalar_t__ REQUEST_SENSE ; 
 int aha152x_internal_queue (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void (*) (TYPE_1__*)) ; 

__attribute__((used)) static int aha152x_queue(Scsi_Cmnd *SCpnt, void (*done)(Scsi_Cmnd *))
{
#if 0
	if(*SCpnt->cmnd == REQUEST_SENSE) {
		SCpnt->result = 0;
		done(SCpnt);

		return 0;
	}
#endif

	return aha152x_internal_queue(SCpnt, NULL, 0, done);
}