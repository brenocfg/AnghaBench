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
typedef  size_t u16 ;
struct r8a66597_device {int /*<<< orphan*/  dma_map; int /*<<< orphan*/  address; scalar_t__* pipe_cnt; } ;
struct r8a66597 {int /*<<< orphan*/  dma_map; int /*<<< orphan*/ * pipe_cnt; } ;

/* Variables and functions */
 size_t R8A66597_MAX_NUM_PIPE ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  force_dequeue (struct r8a66597*,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_r8a66597_pipe_all(struct r8a66597 *r8a66597,
				      struct r8a66597_device *dev)
{
	int check_ep0 = 0;
	u16 pipenum;

	if (!dev)
		return;

	for (pipenum = 1; pipenum < R8A66597_MAX_NUM_PIPE; pipenum++) {
		if (!dev->pipe_cnt[pipenum])
			continue;

		if (!check_ep0) {
			check_ep0 = 1;
			force_dequeue(r8a66597, 0, dev->address);
		}

		r8a66597->pipe_cnt[pipenum] -= dev->pipe_cnt[pipenum];
		dev->pipe_cnt[pipenum] = 0;
		force_dequeue(r8a66597, pipenum, dev->address);
	}

	dbg("disable_pipe");

	r8a66597->dma_map &= ~(dev->dma_map);
	dev->dma_map = 0;
}