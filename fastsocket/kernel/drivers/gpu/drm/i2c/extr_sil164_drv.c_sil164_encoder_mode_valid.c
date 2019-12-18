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
struct sil164_priv {int /*<<< orphan*/  duallink_slave; } ;
struct drm_encoder {int dummy; } ;
struct drm_display_mode {int clock; } ;

/* Variables and functions */
 int MODE_CLOCK_HIGH ; 
 int MODE_CLOCK_LOW ; 
 int MODE_OK ; 
 struct sil164_priv* to_sil164_priv (struct drm_encoder*) ; 

__attribute__((used)) static int
sil164_encoder_mode_valid(struct drm_encoder *encoder,
			  struct drm_display_mode *mode)
{
	struct sil164_priv *priv = to_sil164_priv(encoder);

	if (mode->clock < 32000)
		return MODE_CLOCK_LOW;

	if (mode->clock > 330000 ||
	    (mode->clock > 165000 && !priv->duallink_slave))
		return MODE_CLOCK_HIGH;

	return MODE_OK;
}