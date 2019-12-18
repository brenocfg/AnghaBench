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
struct request_queue {int dummy; } ;
struct request {int dummy; } ;
struct bio {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  blkg; } ;

/* Variables and functions */
 TYPE_1__* RQ_CFQG (struct request*) ; 
 int /*<<< orphan*/  bio_data_dir (struct bio*) ; 
 int /*<<< orphan*/  cfq_bio_sync (struct bio*) ; 
 int /*<<< orphan*/  cfq_blkiocg_update_io_merged_stats (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cfq_bio_merged(struct request_queue *q, struct request *req,
				struct bio *bio)
{
	cfq_blkiocg_update_io_merged_stats(&(RQ_CFQG(req))->blkg,
					bio_data_dir(bio), cfq_bio_sync(bio));
}