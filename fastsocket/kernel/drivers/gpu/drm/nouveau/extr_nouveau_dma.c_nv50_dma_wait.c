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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int free; int cur; int max; scalar_t__ put; } ;
struct nouveau_channel {TYPE_1__ dma; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int READ_GET (struct nouveau_channel*,int /*<<< orphan*/ *,int*) ; 
 int nv50_dma_push_wait (struct nouveau_channel*,int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int
nv50_dma_wait(struct nouveau_channel *chan, int slots, int count)
{
	uint64_t prev_get = 0;
	int ret, cnt = 0;

	ret = nv50_dma_push_wait(chan, slots + 1);
	if (unlikely(ret))
		return ret;

	while (chan->dma.free < count) {
		int get = READ_GET(chan, &prev_get, &cnt);
		if (unlikely(get < 0)) {
			if (get == -EINVAL)
				continue;

			return get;
		}

		if (get <= chan->dma.cur) {
			chan->dma.free = chan->dma.max - chan->dma.cur;
			if (chan->dma.free >= count)
				break;

			FIRE_RING(chan);
			do {
				get = READ_GET(chan, &prev_get, &cnt);
				if (unlikely(get < 0)) {
					if (get == -EINVAL)
						continue;
					return get;
				}
			} while (get == 0);
			chan->dma.cur = 0;
			chan->dma.put = 0;
		}

		chan->dma.free = get - chan->dma.cur - 1;
	}

	return 0;
}