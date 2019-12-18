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
struct radeon_unpin_work {int new_crtc_base; int /*<<< orphan*/  fence; struct radeon_bo* old_rbo; int /*<<< orphan*/  work; int /*<<< orphan*/  crtc_id; struct radeon_device* rdev; struct drm_pending_vblank_event* event; } ;
struct radeon_framebuffer {struct drm_gem_object* obj; } ;
struct radeon_device {int dummy; } ;
struct radeon_crtc {struct radeon_unpin_work* unpin_work; int /*<<< orphan*/  crtc_id; scalar_t__ legacy_display_base_addr; scalar_t__ deferred_flip_completion; } ;
struct TYPE_4__ {TYPE_1__* bdev; scalar_t__ sync_obj; } ;
struct radeon_bo {TYPE_2__ tbo; } ;
struct drm_pending_vblank_event {int dummy; } ;
struct drm_gem_object {int dummy; } ;
struct drm_framebuffer {int* pitches; int bits_per_pixel; } ;
struct drm_device {int /*<<< orphan*/  event_lock; struct radeon_device* dev_private; } ;
struct drm_crtc {int y; int x; struct drm_framebuffer* fb; struct drm_device* dev; } ;
struct TYPE_3__ {int /*<<< orphan*/  fence_lock; } ;

/* Variables and functions */
 scalar_t__ ASIC_IS_AVIVO (struct radeon_device*) ; 
 scalar_t__ ASIC_IS_R300 (struct radeon_device*) ; 
 int /*<<< orphan*/  DRM_DEBUG_DRIVER (char*,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int EBUSY ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RADEON_GEM_DOMAIN_VRAM ; 
 int RADEON_TILING_MACRO ; 
 int /*<<< orphan*/  drm_gem_object_reference (struct drm_gem_object*) ; 
 int /*<<< orphan*/  drm_gem_object_unreference_unlocked (struct drm_gem_object*) ; 
 int drm_vblank_get (struct drm_device*,int /*<<< orphan*/ ) ; 
 struct radeon_bo* gem_to_radeon_bo (struct drm_gem_object*) ; 
 int /*<<< orphan*/  kfree (struct radeon_unpin_work*) ; 
 struct radeon_unpin_work* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_bo_get_tiling_flags (struct radeon_bo*,int*,int /*<<< orphan*/ *) ; 
 int radeon_bo_pin_restricted (struct radeon_bo*,int /*<<< orphan*/ ,int,int*) ; 
 int radeon_bo_reserve (struct radeon_bo*,int) ; 
 scalar_t__ radeon_bo_unpin (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_bo_unreserve (struct radeon_bo*) ; 
 int /*<<< orphan*/  radeon_fence_ref (scalar_t__) ; 
 int /*<<< orphan*/  radeon_fence_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_pre_page_flip (struct radeon_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  radeon_unpin_work_func ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct radeon_crtc* to_radeon_crtc (struct drm_crtc*) ; 
 struct radeon_framebuffer* to_radeon_framebuffer (struct drm_framebuffer*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int radeon_crtc_page_flip(struct drm_crtc *crtc,
				 struct drm_framebuffer *fb,
				 struct drm_pending_vblank_event *event)
{
	struct drm_device *dev = crtc->dev;
	struct radeon_device *rdev = dev->dev_private;
	struct radeon_crtc *radeon_crtc = to_radeon_crtc(crtc);
	struct radeon_framebuffer *old_radeon_fb;
	struct radeon_framebuffer *new_radeon_fb;
	struct drm_gem_object *obj;
	struct radeon_bo *rbo;
	struct radeon_unpin_work *work;
	unsigned long flags;
	u32 tiling_flags, pitch_pixels;
	u64 base;
	int r;

	work = kzalloc(sizeof *work, GFP_KERNEL);
	if (work == NULL)
		return -ENOMEM;

	work->event = event;
	work->rdev = rdev;
	work->crtc_id = radeon_crtc->crtc_id;
	old_radeon_fb = to_radeon_framebuffer(crtc->fb);
	new_radeon_fb = to_radeon_framebuffer(fb);
	/* schedule unpin of the old buffer */
	obj = old_radeon_fb->obj;
	/* take a reference to the old object */
	drm_gem_object_reference(obj);
	rbo = gem_to_radeon_bo(obj);
	work->old_rbo = rbo;
	obj = new_radeon_fb->obj;
	rbo = gem_to_radeon_bo(obj);

	spin_lock(&rbo->tbo.bdev->fence_lock);
	if (rbo->tbo.sync_obj)
		work->fence = radeon_fence_ref(rbo->tbo.sync_obj);
	spin_unlock(&rbo->tbo.bdev->fence_lock);

	INIT_WORK(&work->work, radeon_unpin_work_func);

	/* We borrow the event spin lock for protecting unpin_work */
	spin_lock_irqsave(&dev->event_lock, flags);
	if (radeon_crtc->unpin_work) {
		DRM_DEBUG_DRIVER("flip queue: crtc already busy\n");
		r = -EBUSY;
		goto unlock_free;
	}
	radeon_crtc->unpin_work = work;
	radeon_crtc->deferred_flip_completion = 0;
	spin_unlock_irqrestore(&dev->event_lock, flags);

	/* pin the new buffer */
	DRM_DEBUG_DRIVER("flip-ioctl() cur_fbo = %p, cur_bbo = %p\n",
			 work->old_rbo, rbo);

	r = radeon_bo_reserve(rbo, false);
	if (unlikely(r != 0)) {
		DRM_ERROR("failed to reserve new rbo buffer before flip\n");
		goto pflip_cleanup;
	}
	/* Only 27 bit offset for legacy CRTC */
	r = radeon_bo_pin_restricted(rbo, RADEON_GEM_DOMAIN_VRAM,
				     ASIC_IS_AVIVO(rdev) ? 0 : 1 << 27, &base);
	if (unlikely(r != 0)) {
		radeon_bo_unreserve(rbo);
		r = -EINVAL;
		DRM_ERROR("failed to pin new rbo buffer before flip\n");
		goto pflip_cleanup;
	}
	radeon_bo_get_tiling_flags(rbo, &tiling_flags, NULL);
	radeon_bo_unreserve(rbo);

	if (!ASIC_IS_AVIVO(rdev)) {
		/* crtc offset is from display base addr not FB location */
		base -= radeon_crtc->legacy_display_base_addr;
		pitch_pixels = fb->pitches[0] / (fb->bits_per_pixel / 8);

		if (tiling_flags & RADEON_TILING_MACRO) {
			if (ASIC_IS_R300(rdev)) {
				base &= ~0x7ff;
			} else {
				int byteshift = fb->bits_per_pixel >> 4;
				int tile_addr = (((crtc->y >> 3) * pitch_pixels +  crtc->x) >> (8 - byteshift)) << 11;
				base += tile_addr + ((crtc->x << byteshift) % 256) + ((crtc->y % 8) << 8);
			}
		} else {
			int offset = crtc->y * pitch_pixels + crtc->x;
			switch (fb->bits_per_pixel) {
			case 8:
			default:
				offset *= 1;
				break;
			case 15:
			case 16:
				offset *= 2;
				break;
			case 24:
				offset *= 3;
				break;
			case 32:
				offset *= 4;
				break;
			}
			base += offset;
		}
		base &= ~7;
	}

	spin_lock_irqsave(&dev->event_lock, flags);
	work->new_crtc_base = base;
	spin_unlock_irqrestore(&dev->event_lock, flags);

	/* update crtc fb */
	crtc->fb = fb;

	r = drm_vblank_get(dev, radeon_crtc->crtc_id);
	if (r) {
		DRM_ERROR("failed to get vblank before flip\n");
		goto pflip_cleanup1;
	}

	/* set the proper interrupt */
	radeon_pre_page_flip(rdev, radeon_crtc->crtc_id);

	return 0;

pflip_cleanup1:
	if (unlikely(radeon_bo_reserve(rbo, false) != 0)) {
		DRM_ERROR("failed to reserve new rbo in error path\n");
		goto pflip_cleanup;
	}
	if (unlikely(radeon_bo_unpin(rbo) != 0)) {
		DRM_ERROR("failed to unpin new rbo in error path\n");
	}
	radeon_bo_unreserve(rbo);

pflip_cleanup:
	spin_lock_irqsave(&dev->event_lock, flags);
	radeon_crtc->unpin_work = NULL;
unlock_free:
	spin_unlock_irqrestore(&dev->event_lock, flags);
	drm_gem_object_unreference_unlocked(old_radeon_fb->obj);
	radeon_fence_unref(&work->fence);
	kfree(work);

	return r;
}