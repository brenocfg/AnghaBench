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
struct request_queue {struct mapped_device* queuedata; } ;
struct mapped_device {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int _dm_request (struct request_queue*,struct bio*) ; 
 int blk_queue_bio (struct request_queue*,struct bio*) ; 
 scalar_t__ dm_request_based (struct mapped_device*) ; 

__attribute__((used)) static int dm_request(struct request_queue *q, struct bio *bio)
{
	struct mapped_device *md = q->queuedata;

	if (dm_request_based(md))
		return blk_queue_bio(q, bio);

	return _dm_request(q, bio);
}