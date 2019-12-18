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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int /*<<< orphan*/  user; } ;
struct nv50_dmac {int /*<<< orphan*/  lock; int /*<<< orphan*/ * ptr; TYPE_1__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nv_wo32 (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
evo_kick(u32 *push, void *evoc)
{
	struct nv50_dmac *dmac = evoc;
	nv_wo32(dmac->base.user, 0x0000, (push - dmac->ptr) << 2);
	mutex_unlock(&dmac->lock);
}