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
struct tape_device {int dummy; } ;
struct request_queue {scalar_t__ queuedata; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBF_LH (int,char*,struct tape_device*) ; 
 int /*<<< orphan*/  tapeblock_trigger_requeue (struct tape_device*) ; 

__attribute__((used)) static void
tapeblock_request_fn(struct request_queue *queue)
{
	struct tape_device *device;

	device = (struct tape_device *) queue->queuedata;
	DBF_LH(6, "tapeblock_request_fn(device=%p)\n", device);
	BUG_ON(device == NULL);
	tapeblock_trigger_requeue(device);
}