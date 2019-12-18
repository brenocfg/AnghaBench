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
typedef  int /*<<< orphan*/  u64 ;
struct nv84_fence_chan {TYPE_1__* dispc_vma; } ;
struct nouveau_channel {struct nv84_fence_chan* fence; } ;
struct TYPE_2__ {int /*<<< orphan*/  offset; } ;

/* Variables and functions */

u64
nv84_fence_crtc(struct nouveau_channel *chan, int crtc)
{
	struct nv84_fence_chan *fctx = chan->fence;
	return fctx->dispc_vma[crtc].offset;
}