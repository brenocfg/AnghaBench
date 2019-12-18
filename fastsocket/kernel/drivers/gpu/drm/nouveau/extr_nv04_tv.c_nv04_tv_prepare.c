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
struct drm_encoder_helper_funcs {int /*<<< orphan*/  (* dpms ) (struct drm_encoder*,int /*<<< orphan*/ ) ;} ;
struct drm_encoder {struct drm_encoder_helper_funcs* helper_private; int /*<<< orphan*/  crtc; struct drm_device* dev; } ;
struct drm_device {int dummy; } ;
struct TYPE_2__ {int index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_MODE_DPMS_OFF ; 
 TYPE_1__* nouveau_crtc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv04_dfp_disable (struct drm_device*,int) ; 
 int /*<<< orphan*/  nv04_tv_bind (struct drm_device*,int,int) ; 
 scalar_t__ nv_two_heads (struct drm_device*) ; 
 int /*<<< orphan*/  stub1 (struct drm_encoder*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nv04_tv_prepare(struct drm_encoder *encoder)
{
	struct drm_device *dev = encoder->dev;
	int head = nouveau_crtc(encoder->crtc)->index;
	struct drm_encoder_helper_funcs *helper = encoder->helper_private;

	helper->dpms(encoder, DRM_MODE_DPMS_OFF);

	nv04_dfp_disable(dev, head);

	if (nv_two_heads(dev))
		nv04_tv_bind(dev, head ^ 1, false);

	nv04_tv_bind(dev, head, true);
}