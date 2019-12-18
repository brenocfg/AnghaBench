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
struct nouveau_drm {struct backlight_device* backlight; int /*<<< orphan*/  device; } ;
struct nouveau_device {int dummy; } ;
struct drm_connector {int /*<<< orphan*/  kdev; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int max_brightness; int /*<<< orphan*/  brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int /*<<< orphan*/  NV40_PMC_BACKLIGHT ; 
 int NV40_PMC_BACKLIGHT_MASK ; 
 int PTR_ERR (struct backlight_device*) ; 
 struct backlight_device* backlight_device_register (char*,int /*<<< orphan*/ *,struct nouveau_drm*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 struct nouveau_drm* nouveau_drm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nv40_bl_ops ; 
 int /*<<< orphan*/  nv40_get_intensity (struct backlight_device*) ; 
 struct nouveau_device* nv_device (int /*<<< orphan*/ ) ; 
 int nv_rd32 (struct nouveau_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nv40_backlight_init(struct drm_connector *connector)
{
	struct nouveau_drm *drm = nouveau_drm(connector->dev);
	struct nouveau_device *device = nv_device(drm->device);
	struct backlight_device *bd;

	if (!(nv_rd32(device, NV40_PMC_BACKLIGHT) & NV40_PMC_BACKLIGHT_MASK))
		return 0;

	bd = backlight_device_register("nv_backlight", &connector->kdev, drm,
				       &nv40_bl_ops);
	if (IS_ERR(bd))
		return PTR_ERR(bd);
	drm->backlight = bd;
	bd->props.brightness = nv40_get_intensity(bd);
	bd->props.max_brightness = 31;
	backlight_update_status(bd);

	return 0;
}