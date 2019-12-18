#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct request {scalar_t__ cmd_type; scalar_t__* cmd; int /*<<< orphan*/  errors; } ;
struct TYPE_6__ {TYPE_1__* hwif; } ;
typedef  TYPE_2__ ide_drive_t ;
struct TYPE_5__ {struct request* rq; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ REQ_DRIVE_RESET ; 
 scalar_t__ REQ_TYPE_SPECIAL ; 
 int /*<<< orphan*/  blk_rq_bytes (struct request*) ; 
 int /*<<< orphan*/  ide_complete_rq (TYPE_2__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void ide_complete_drive_reset(ide_drive_t *drive, int err)
{
	struct request *rq = drive->hwif->rq;

	if (rq && rq->cmd_type == REQ_TYPE_SPECIAL &&
	    rq->cmd[0] == REQ_DRIVE_RESET) {
		if (err <= 0 && rq->errors == 0)
			rq->errors = -EIO;
		ide_complete_rq(drive, err ? err : 0, blk_rq_bytes(rq));
	}
}