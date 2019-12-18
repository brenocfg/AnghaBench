#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct drm_encoder_helper_funcs {int /*<<< orphan*/  (* dpms ) (struct drm_encoder*,int /*<<< orphan*/ ) ;} ;
struct drm_encoder {struct drm_encoder_helper_funcs* helper_private; struct drm_crtc* crtc; } ;
struct drm_crtc_helper_funcs {int /*<<< orphan*/  (* dpms ) (struct drm_crtc*,int /*<<< orphan*/ ) ;} ;
struct drm_crtc {struct drm_crtc_helper_funcs* helper_private; } ;
struct drm_connector {int dpms; struct drm_encoder* encoder; } ;

/* Variables and functions */
 int /*<<< orphan*/  drm_helper_choose_crtc_dpms (struct drm_crtc*) ; 
 int /*<<< orphan*/  drm_helper_choose_encoder_dpms (struct drm_encoder*) ; 
 int /*<<< orphan*/  stub1 (struct drm_crtc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (struct drm_encoder*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct drm_crtc*,int /*<<< orphan*/ ) ; 

void drm_helper_connector_dpms(struct drm_connector *connector, int mode)
{
	struct drm_encoder *encoder = connector->encoder;
	struct drm_crtc *crtc = encoder ? encoder->crtc : NULL;
	int old_dpms;

	if (mode == connector->dpms)
		return;

	old_dpms = connector->dpms;
	connector->dpms = mode;

	/* from off to on, do crtc then encoder */
	if (mode < old_dpms) {
		if (crtc) {
			struct drm_crtc_helper_funcs *crtc_funcs = crtc->helper_private;
			if (crtc_funcs->dpms)
				(*crtc_funcs->dpms) (crtc,
						     drm_helper_choose_crtc_dpms(crtc));
		}
		if (encoder) {
			struct drm_encoder_helper_funcs *encoder_funcs = encoder->helper_private;
			if (encoder_funcs->dpms)
				(*encoder_funcs->dpms) (encoder,
							drm_helper_choose_encoder_dpms(encoder));
		}
	}

	/* from on to off, do encoder then crtc */
	if (mode > old_dpms) {
		if (encoder) {
			struct drm_encoder_helper_funcs *encoder_funcs = encoder->helper_private;
			if (encoder_funcs->dpms)
				(*encoder_funcs->dpms) (encoder,
							drm_helper_choose_encoder_dpms(encoder));
		}
		if (crtc) {
			struct drm_crtc_helper_funcs *crtc_funcs = crtc->helper_private;
			if (crtc_funcs->dpms)
				(*crtc_funcs->dpms) (crtc,
						     drm_helper_choose_crtc_dpms(crtc));
		}
	}

	return;
}