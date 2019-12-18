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
typedef  int u64 ;
struct tv_mode {unsigned int max_srcw; scalar_t__ refresh; int /*<<< orphan*/  component_only; int /*<<< orphan*/  progressive; } ;
struct intel_tv {int dummy; } ;
struct input_res {unsigned int w; unsigned int h; int /*<<< orphan*/  name; } ;
struct drm_display_mode {unsigned int hdisplay; unsigned int hsync_start; unsigned int hsync_end; unsigned int htotal; unsigned int vdisplay; unsigned int vsync_start; unsigned int vsync_end; unsigned int vtotal; int clock; int /*<<< orphan*/  type; int /*<<< orphan*/  name; } ;
struct drm_connector {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct input_res*) ; 
 int /*<<< orphan*/  DRM_DISPLAY_MODE_LEN ; 
 int /*<<< orphan*/  DRM_MODE_TYPE_DRIVER ; 
 int div_u64 (int,int) ; 
 struct drm_display_mode* drm_mode_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  drm_mode_probed_add (struct drm_connector*,struct drm_display_mode*) ; 
 struct input_res* input_res_table ; 
 struct intel_tv* intel_attached_tv (struct drm_connector*) ; 
 int /*<<< orphan*/  intel_tv_chose_preferred_modes (struct drm_connector*,struct drm_display_mode*) ; 
 struct tv_mode* intel_tv_mode_find (struct intel_tv*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_tv_get_modes(struct drm_connector *connector)
{
	struct drm_display_mode *mode_ptr;
	struct intel_tv *intel_tv = intel_attached_tv(connector);
	const struct tv_mode *tv_mode = intel_tv_mode_find(intel_tv);
	int j, count = 0;
	u64 tmp;

	for (j = 0; j < ARRAY_SIZE(input_res_table);
	     j++) {
		const struct input_res *input = &input_res_table[j];
		unsigned int hactive_s = input->w;
		unsigned int vactive_s = input->h;

		if (tv_mode->max_srcw && input->w > tv_mode->max_srcw)
			continue;

		if (input->w > 1024 && (!tv_mode->progressive
					&& !tv_mode->component_only))
			continue;

		mode_ptr = drm_mode_create(connector->dev);
		if (!mode_ptr)
			continue;
		strncpy(mode_ptr->name, input->name, DRM_DISPLAY_MODE_LEN);

		mode_ptr->hdisplay = hactive_s;
		mode_ptr->hsync_start = hactive_s + 1;
		mode_ptr->hsync_end = hactive_s + 64;
		if (mode_ptr->hsync_end <= mode_ptr->hsync_start)
			mode_ptr->hsync_end = mode_ptr->hsync_start + 1;
		mode_ptr->htotal = hactive_s + 96;

		mode_ptr->vdisplay = vactive_s;
		mode_ptr->vsync_start = vactive_s + 1;
		mode_ptr->vsync_end = vactive_s + 32;
		if (mode_ptr->vsync_end <= mode_ptr->vsync_start)
			mode_ptr->vsync_end = mode_ptr->vsync_start  + 1;
		mode_ptr->vtotal = vactive_s + 33;

		tmp = (u64) tv_mode->refresh * mode_ptr->vtotal;
		tmp *= mode_ptr->htotal;
		tmp = div_u64(tmp, 1000000);
		mode_ptr->clock = (int) tmp;

		mode_ptr->type = DRM_MODE_TYPE_DRIVER;
		intel_tv_chose_preferred_modes(connector, mode_ptr);
		drm_mode_probed_add(connector, mode_ptr);
		count++;
	}

	return count;
}