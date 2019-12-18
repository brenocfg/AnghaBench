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
typedef  int uint32_t ;
typedef  void* u16 ;
struct TYPE_4__ {scalar_t__ depth; void** b; void** g; void** r; } ;
struct TYPE_3__ {int /*<<< orphan*/  fb; } ;
struct nouveau_crtc {TYPE_2__ lut; TYPE_1__ base; } ;
struct drm_crtc {int dummy; } ;

/* Variables and functions */
 struct nouveau_crtc* nouveau_crtc (struct drm_crtc*) ; 
 int /*<<< orphan*/  nv_crtc_gamma_load (struct drm_crtc*) ; 

__attribute__((used)) static void
nv_crtc_gamma_set(struct drm_crtc *crtc, u16 *r, u16 *g, u16 *b, uint32_t start,
		  uint32_t size)
{
	int end = (start + size > 256) ? 256 : start + size, i;
	struct nouveau_crtc *nv_crtc = nouveau_crtc(crtc);

	for (i = start; i < end; i++) {
		nv_crtc->lut.r[i] = r[i];
		nv_crtc->lut.g[i] = g[i];
		nv_crtc->lut.b[i] = b[i];
	}

	/* We need to know the depth before we upload, but it's possible to
	 * get called before a framebuffer is bound.  If this is the case,
	 * mark the lut values as dirty by setting depth==0, and it'll be
	 * uploaded on the first mode_set_base()
	 */
	if (!nv_crtc->base.fb) {
		nv_crtc->lut.depth = 0;
		return;
	}

	nv_crtc_gamma_load(crtc);
}