#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct request_queue {TYPE_1__* queuedata; } ;
struct gendisk {int major; int first_minor; int /*<<< orphan*/ * fops; int /*<<< orphan*/  disk_name; struct request_queue* queue; } ;
struct TYPE_3__ {int ControllerNumber; int /*<<< orphan*/  MaxBlocksPerCommand; int /*<<< orphan*/  DriverScatterGatherLimit; int /*<<< orphan*/  BounceBufferLimit; struct request_queue** RequestQueue; int /*<<< orphan*/  queue_lock; struct gendisk** disks; } ;
typedef  TYPE_1__ DAC960_Controller_T ;

/* Variables and functions */
 int /*<<< orphan*/  DAC960_BlockDeviceOperations ; 
 int DAC960_MAJOR ; 
 int DAC960_MaxLogicalDrives ; 
 int DAC960_MaxPartitionsBits ; 
 int /*<<< orphan*/  DAC960_RequestFunction ; 
 struct request_queue* blk_init_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_queue_bounce_limit (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_segments (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printk (char*) ; 
 scalar_t__ register_blkdev (int,char*) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int,int) ; 

__attribute__((used)) static bool DAC960_RegisterBlockDevice(DAC960_Controller_T *Controller)
{
  int MajorNumber = DAC960_MAJOR + Controller->ControllerNumber;
  int n;

  /*
    Register the Block Device Major Number for this DAC960 Controller.
  */
  if (register_blkdev(MajorNumber, "dac960") < 0)
      return false;

  for (n = 0; n < DAC960_MaxLogicalDrives; n++) {
	struct gendisk *disk = Controller->disks[n];
  	struct request_queue *RequestQueue;

	/* for now, let all request queues share controller's lock */
  	RequestQueue = blk_init_queue(DAC960_RequestFunction,&Controller->queue_lock);
  	if (!RequestQueue) {
		printk("DAC960: failure to allocate request queue\n");
		continue;
  	}
  	Controller->RequestQueue[n] = RequestQueue;
  	blk_queue_bounce_limit(RequestQueue, Controller->BounceBufferLimit);
  	RequestQueue->queuedata = Controller;
	blk_queue_max_segments(RequestQueue, Controller->DriverScatterGatherLimit);
	blk_queue_max_hw_sectors(RequestQueue, Controller->MaxBlocksPerCommand);
	disk->queue = RequestQueue;
	sprintf(disk->disk_name, "rd/c%dd%d", Controller->ControllerNumber, n);
	disk->major = MajorNumber;
	disk->first_minor = n << DAC960_MaxPartitionsBits;
	disk->fops = &DAC960_BlockDeviceOperations;
   }
  /*
    Indicate the Block Device Registration completed successfully,
  */
  return true;
}