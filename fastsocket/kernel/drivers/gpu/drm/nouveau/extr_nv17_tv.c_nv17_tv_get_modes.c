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
struct nv17_tv_norm_params {scalar_t__ kind; } ;
struct drm_encoder {int dummy; } ;
struct drm_connector {int dummy; } ;

/* Variables and functions */
 scalar_t__ CTV_ENC_MODE ; 
 struct nv17_tv_norm_params* get_tv_norm (struct drm_encoder*) ; 
 int nv17_tv_get_hd_modes (struct drm_encoder*,struct drm_connector*) ; 
 int nv17_tv_get_ld_modes (struct drm_encoder*,struct drm_connector*) ; 

__attribute__((used)) static int nv17_tv_get_modes(struct drm_encoder *encoder,
			     struct drm_connector *connector)
{
	struct nv17_tv_norm_params *tv_norm = get_tv_norm(encoder);

	if (tv_norm->kind == CTV_ENC_MODE)
		return nv17_tv_get_hd_modes(encoder, connector);
	else
		return nv17_tv_get_ld_modes(encoder, connector);
}