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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  user; } ;
struct nv50_dmac {int* ptr; TYPE_1__ base; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  NV_ERROR (int /*<<< orphan*/ ,char*) ; 
 int PAGE_SIZE ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int nv_ro32 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv_wait (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static u32 *
evo_wait(void *evoc, int nr)
{
	struct nv50_dmac *dmac = evoc;
	u32 put = nv_ro32(dmac->base.user, 0x0000) / 4;

	mutex_lock(&dmac->lock);
	if (put + nr >= (PAGE_SIZE / 4) - 8) {
		dmac->ptr[put] = 0x20000000;

		nv_wo32(dmac->base.user, 0x0000, 0x00000000);
		if (!nv_wait(dmac->base.user, 0x0004, ~0, 0x00000000)) {
			mutex_unlock(&dmac->lock);
			NV_ERROR(dmac->base.user, "channel stalled\n");
			return NULL;
		}

		put = 0;
	}

	return dmac->ptr + put;
}