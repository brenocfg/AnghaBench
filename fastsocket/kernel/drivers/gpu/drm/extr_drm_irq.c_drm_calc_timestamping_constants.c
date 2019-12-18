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
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_3__ {int flags; int crtc_htotal; int crtc_vtotal; int /*<<< orphan*/  crtc_vdisplay; scalar_t__ clock; } ;
struct drm_crtc {TYPE_2__ base; TYPE_1__ hwmode; void* framedur_ns; void* linedur_ns; void* pixeldur_ns; } ;
typedef  void* s64 ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_DEBUG (char*,int /*<<< orphan*/ ,int,int,int,...) ; 
 int /*<<< orphan*/  DRM_ERROR (char*,int /*<<< orphan*/ ) ; 
 int DRM_MODE_FLAG_INTERLACE ; 
 scalar_t__ div64_u64 (int,int) ; 

void drm_calc_timestamping_constants(struct drm_crtc *crtc)
{
	s64 linedur_ns = 0, pixeldur_ns = 0, framedur_ns = 0;
	u64 dotclock;

	/* Dot clock in Hz: */
	dotclock = (u64) crtc->hwmode.clock * 1000;

	/* Fields of interlaced scanout modes are only halve a frame duration.
	 * Double the dotclock to get halve the frame-/line-/pixelduration.
	 */
	if (crtc->hwmode.flags & DRM_MODE_FLAG_INTERLACE)
		dotclock *= 2;

	/* Valid dotclock? */
	if (dotclock > 0) {
		int frame_size;
		/* Convert scanline length in pixels and video dot clock to
		 * line duration, frame duration and pixel duration in
		 * nanoseconds:
		 */
		pixeldur_ns = (s64) div64_u64(1000000000, dotclock);
		linedur_ns  = (s64) div64_u64(((u64) crtc->hwmode.crtc_htotal *
					      1000000000), dotclock);
		frame_size = crtc->hwmode.crtc_htotal *
				crtc->hwmode.crtc_vtotal;
		framedur_ns = (s64) div64_u64((u64) frame_size * 1000000000,
					      dotclock);
	} else
		DRM_ERROR("crtc %d: Can't calculate constants, dotclock = 0!\n",
			  crtc->base.id);

	crtc->pixeldur_ns = pixeldur_ns;
	crtc->linedur_ns  = linedur_ns;
	crtc->framedur_ns = framedur_ns;

	DRM_DEBUG("crtc %d: hwmode: htotal %d, vtotal %d, vdisplay %d\n",
		  crtc->base.id, crtc->hwmode.crtc_htotal,
		  crtc->hwmode.crtc_vtotal, crtc->hwmode.crtc_vdisplay);
	DRM_DEBUG("crtc %d: clock %d kHz framedur %d linedur %d, pixeldur %d\n",
		  crtc->base.id, (int) dotclock/1000, (int) framedur_ns,
		  (int) linedur_ns, (int) pixeldur_ns);
}