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
struct request_queue {struct pktcdvd_device* queuedata; } ;
struct pktcdvd_device {TYPE_1__* disk; } ;
struct TYPE_2__ {struct request_queue* queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  CD_FRAMESIZE ; 
 int /*<<< orphan*/  PACKET_MAX_SECTORS ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_make_request (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_merge_bvec (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pkt_make_request ; 
 int /*<<< orphan*/  pkt_merge_bvec ; 

__attribute__((used)) static void pkt_init_queue(struct pktcdvd_device *pd)
{
	struct request_queue *q = pd->disk->queue;

	blk_queue_make_request(q, pkt_make_request);
	blk_queue_logical_block_size(q, CD_FRAMESIZE);
	blk_queue_max_hw_sectors(q, PACKET_MAX_SECTORS);
	blk_queue_merge_bvec(q, pkt_merge_bvec);
	q->queuedata = pd;
}