#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
typedef  int u32 ;
struct nv50_sync {int addr; int data; } ;
struct nouveau_framebuffer {int r_dma; int r_pitch; int r_format; TYPE_2__* nvbo; } ;
struct nouveau_crtc {int index; } ;
struct nouveau_channel {int vram; int /*<<< orphan*/  object; } ;
struct drm_framebuffer {int height; int width; } ;
struct drm_crtc {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {int offset; } ;
struct TYPE_4__ {TYPE_1__ bo; } ;

/* Variables and functions */
 int /*<<< orphan*/  BEGIN_NV04 (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  BEGIN_NVC0 (struct nouveau_channel*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int EBUSY ; 
 int /*<<< orphan*/  FIRE_RING (struct nouveau_channel*) ; 
 int /*<<< orphan*/  NV11_SUBCHAN_DMA_SEMAPHORE ; 
 int /*<<< orphan*/  NV11_SUBCHAN_SEMAPHORE_OFFSET ; 
 int /*<<< orphan*/  NV11_SUBCHAN_SEMAPHORE_RELEASE ; 
 scalar_t__ NV84_CHANNEL_IND_CLASS ; 
 int /*<<< orphan*/  NV84_SUBCHAN_SEMAPHORE_ADDRESS_HIGH ; 
 int NV84_SUBCHAN_SEMAPHORE_TRIGGER_ACQUIRE_EQUAL ; 
 int NV84_SUBCHAN_SEMAPHORE_TRIGGER_WRITE_LONG ; 
 scalar_t__ NVC0_CHANNEL_IND_CLASS ; 
 int NVC0_SUBCHAN_SEMAPHORE_TRIGGER_YIELD ; 
 scalar_t__ NVD0_DISP_SYNC_CLASS ; 
 int NvEvoSema0 ; 
 int NvEvoSync ; 
 int /*<<< orphan*/  OUT_RING (struct nouveau_channel*,int) ; 
 int RING_SPACE (struct nouveau_channel*,int) ; 
 int /*<<< orphan*/  evo_data (int*,int) ; 
 int /*<<< orphan*/  evo_kick (int*,struct nv50_sync*) ; 
 int /*<<< orphan*/  evo_mthd (int*,int,int) ; 
 int /*<<< orphan*/  evo_sync (int /*<<< orphan*/ ) ; 
 int* evo_wait (struct nv50_sync*,int) ; 
 int lower_32_bits (int) ; 
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 struct nouveau_framebuffer* nouveau_framebuffer (struct drm_framebuffer*) ; 
 struct nv50_sync* nv50_sync (struct drm_crtc*) ; 
 scalar_t__ nv50_vers (struct nv50_sync*) ; 
 int nv84_fence_crtc (struct nouveau_channel*,int) ; 
 scalar_t__ nv_mclass (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int upper_32_bits (int) ; 

int
nv50_display_flip_next(struct drm_crtc *crtc, struct drm_framebuffer *fb,
		       struct nouveau_channel *chan, u32 swap_interval)
{
	struct nouveau_framebuffer *nv_fb = nouveau_framebuffer(fb);
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);
	struct nv50_sync *sync = nv50_sync(crtc);
	int head = nv_crtc->index, ret;
	u32 *push;

	swap_interval <<= 4;
	if (swap_interval == 0)
		swap_interval |= 0x100;
	if (chan == NULL)
		evo_sync(crtc->dev);

	push = evo_wait(sync, 128);
	if (unlikely(push == NULL))
		return -EBUSY;

	if (chan && nv_mclass(chan->object) < NV84_CHANNEL_IND_CLASS) {
		ret = RING_SPACE(chan, 8);
		if (ret)
			return ret;

		BEGIN_NV04(chan, 0, NV11_SUBCHAN_DMA_SEMAPHORE, 2);
		OUT_RING  (chan, NvEvoSema0 + head);
		OUT_RING  (chan, sync->addr ^ 0x10);
		BEGIN_NV04(chan, 0, NV11_SUBCHAN_SEMAPHORE_RELEASE, 1);
		OUT_RING  (chan, sync->data + 1);
		BEGIN_NV04(chan, 0, NV11_SUBCHAN_SEMAPHORE_OFFSET, 2);
		OUT_RING  (chan, sync->addr);
		OUT_RING  (chan, sync->data);
	} else
	if (chan && nv_mclass(chan->object) < NVC0_CHANNEL_IND_CLASS) {
		u64 addr = nv84_fence_crtc(chan, head) + sync->addr;
		ret = RING_SPACE(chan, 12);
		if (ret)
			return ret;

		BEGIN_NV04(chan, 0, NV11_SUBCHAN_DMA_SEMAPHORE, 1);
		OUT_RING  (chan, chan->vram);
		BEGIN_NV04(chan, 0, NV84_SUBCHAN_SEMAPHORE_ADDRESS_HIGH, 4);
		OUT_RING  (chan, upper_32_bits(addr ^ 0x10));
		OUT_RING  (chan, lower_32_bits(addr ^ 0x10));
		OUT_RING  (chan, sync->data + 1);
		OUT_RING  (chan, NV84_SUBCHAN_SEMAPHORE_TRIGGER_WRITE_LONG);
		BEGIN_NV04(chan, 0, NV84_SUBCHAN_SEMAPHORE_ADDRESS_HIGH, 4);
		OUT_RING  (chan, upper_32_bits(addr));
		OUT_RING  (chan, lower_32_bits(addr));
		OUT_RING  (chan, sync->data);
		OUT_RING  (chan, NV84_SUBCHAN_SEMAPHORE_TRIGGER_ACQUIRE_EQUAL);
	} else
	if (chan) {
		u64 addr = nv84_fence_crtc(chan, head) + sync->addr;
		ret = RING_SPACE(chan, 10);
		if (ret)
			return ret;

		BEGIN_NVC0(chan, 0, NV84_SUBCHAN_SEMAPHORE_ADDRESS_HIGH, 4);
		OUT_RING  (chan, upper_32_bits(addr ^ 0x10));
		OUT_RING  (chan, lower_32_bits(addr ^ 0x10));
		OUT_RING  (chan, sync->data + 1);
		OUT_RING  (chan, NV84_SUBCHAN_SEMAPHORE_TRIGGER_WRITE_LONG |
				 NVC0_SUBCHAN_SEMAPHORE_TRIGGER_YIELD);
		BEGIN_NVC0(chan, 0, NV84_SUBCHAN_SEMAPHORE_ADDRESS_HIGH, 4);
		OUT_RING  (chan, upper_32_bits(addr));
		OUT_RING  (chan, lower_32_bits(addr));
		OUT_RING  (chan, sync->data);
		OUT_RING  (chan, NV84_SUBCHAN_SEMAPHORE_TRIGGER_ACQUIRE_EQUAL |
				 NVC0_SUBCHAN_SEMAPHORE_TRIGGER_YIELD);
	}

	if (chan) {
		sync->addr ^= 0x10;
		sync->data++;
		FIRE_RING (chan);
	}

	/* queue the flip */
	evo_mthd(push, 0x0100, 1);
	evo_data(push, 0xfffe0000);
	evo_mthd(push, 0x0084, 1);
	evo_data(push, swap_interval);
	if (!(swap_interval & 0x00000100)) {
		evo_mthd(push, 0x00e0, 1);
		evo_data(push, 0x40000000);
	}
	evo_mthd(push, 0x0088, 4);
	evo_data(push, sync->addr);
	evo_data(push, sync->data++);
	evo_data(push, sync->data);
	evo_data(push, NvEvoSync);
	evo_mthd(push, 0x00a0, 2);
	evo_data(push, 0x00000000);
	evo_data(push, 0x00000000);
	evo_mthd(push, 0x00c0, 1);
	evo_data(push, nv_fb->r_dma);
	evo_mthd(push, 0x0110, 2);
	evo_data(push, 0x00000000);
	evo_data(push, 0x00000000);
	if (nv50_vers(sync) < NVD0_DISP_SYNC_CLASS) {
		evo_mthd(push, 0x0800, 5);
		evo_data(push, nv_fb->nvbo->bo.offset >> 8);
		evo_data(push, 0);
		evo_data(push, (fb->height << 16) | fb->width);
		evo_data(push, nv_fb->r_pitch);
		evo_data(push, nv_fb->r_format);
	} else {
		evo_mthd(push, 0x0400, 5);
		evo_data(push, nv_fb->nvbo->bo.offset >> 8);
		evo_data(push, 0);
		evo_data(push, (fb->height << 16) | fb->width);
		evo_data(push, nv_fb->r_pitch);
		evo_data(push, nv_fb->r_format);
	}
	evo_mthd(push, 0x0080, 1);
	evo_data(push, 0x00000000);
	evo_kick(push, sync);
	return 0;
}