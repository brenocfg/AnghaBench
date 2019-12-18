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
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int dummy; } ;

/* Variables and functions */
 int MODE_BAD ; 
 int MODE_OK ; 
 scalar_t__ ch7006_lookup_mode (struct drm_encoder*,struct drm_display_mode*) ; 

__attribute__((used)) static int ch7006_encoder_mode_valid(struct drm_encoder *encoder,
				     struct drm_display_mode *mode)
{
	if (ch7006_lookup_mode(encoder, mode))
		return MODE_OK;
	else
		return MODE_BAD;
}