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
struct nouveau_fence {int /*<<< orphan*/  sequence; struct nouveau_channel* channel; } ;
struct nouveau_channel {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NV10_SUBCHAN_REF_CNT ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int /*<<< orphan*/ ) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 

int
nv10_fence_emit(struct nouveau_fence *fence)
{
	struct nouveau_channel *chan = fence->channel;
	int ret = RING_SPACE(chan, 2);
	if (ret == 0) {
		BEGIN_NV04(chan, 0, NV10_SUBCHAN_REF_CNT, 1);
		OUT_RING  (chan, fence->sequence);
		FIRE_RING (chan);
	}
	return ret;
}