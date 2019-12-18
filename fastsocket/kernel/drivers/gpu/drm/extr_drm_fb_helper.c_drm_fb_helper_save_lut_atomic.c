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
typedef  int /*<<< orphan*/  uint16_t ;
struct drm_fb_helper {TYPE_1__* funcs; } ;
struct drm_crtc {int gamma_size; int /*<<< orphan*/ * gamma_store; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* gamma_get ) (struct drm_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct drm_crtc*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void drm_fb_helper_save_lut_atomic(struct drm_crtc *crtc, struct drm_fb_helper *helper)
{
	uint16_t *r_base, *g_base, *b_base;
	int i;

	r_base = crtc->gamma_store;
	g_base = r_base + crtc->gamma_size;
	b_base = g_base + crtc->gamma_size;

	for (i = 0; i < crtc->gamma_size; i++)
		helper->funcs->gamma_get(crtc, &r_base[i], &g_base[i], &b_base[i], i);
}