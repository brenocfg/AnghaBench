#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct request {TYPE_1__* rq_disk; } ;
struct TYPE_2__ {scalar_t__ private_data; } ;

/* Variables and functions */
 scalar_t__ __blk_end_request (struct request*,int,unsigned int) ; 
 unsigned int blk_rq_cur_sectors (struct request*) ; 
 unsigned int current_count_sectors ; 
 int /*<<< orphan*/ * current_req ; 
 int /*<<< orphan*/  floppy_off (unsigned int) ; 

__attribute__((used)) static void floppy_end_request(struct request *req, int error)
{
	unsigned int nr_sectors = current_count_sectors;
	unsigned int drive = (unsigned long)req->rq_disk->private_data;

	/* current_count_sectors can be zero if transfer failed */
	if (error)
		nr_sectors = blk_rq_cur_sectors(req);
	if (__blk_end_request(req, error, nr_sectors << 9))
		return;

	/* We're done with the request */
	floppy_off(drive);
	current_req = NULL;
}