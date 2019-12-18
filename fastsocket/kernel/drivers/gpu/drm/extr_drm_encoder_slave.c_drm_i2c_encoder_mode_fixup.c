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
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;
struct TYPE_2__ {int (* mode_fixup ) (struct drm_encoder*,struct drm_display_mode const*,struct drm_display_mode*) ;} ;

/* Variables and functions */
 TYPE_1__* get_slave_funcs (struct drm_encoder*) ; 
 int stub1 (struct drm_encoder*,struct drm_display_mode const*,struct drm_display_mode*) ; 

bool drm_i2c_encoder_mode_fixup(struct drm_encoder *encoder,
		const struct drm_display_mode *mode,
		struct drm_display_mode *adjusted_mode)
{
	return get_slave_funcs(encoder)->mode_fixup(encoder, mode, adjusted_mode);
}