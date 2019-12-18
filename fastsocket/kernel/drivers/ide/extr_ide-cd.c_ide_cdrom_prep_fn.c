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
struct request_queue {int dummy; } ;
struct request {scalar_t__ cmd_type; } ;

/* Variables and functions */
 scalar_t__ REQ_TYPE_BLOCK_PC ; 
 scalar_t__ REQ_TYPE_FS ; 
 int ide_cdrom_prep_fs (struct request_queue*,struct request*) ; 
 int ide_cdrom_prep_pc (struct request*) ; 

__attribute__((used)) static int ide_cdrom_prep_fn(struct request_queue *q, struct request *rq)
{
	if (rq->cmd_type == REQ_TYPE_FS)
		return ide_cdrom_prep_fs(q, rq);
	else if (rq->cmd_type == REQ_TYPE_BLOCK_PC)
		return ide_cdrom_prep_pc(rq);

	return 0;
}