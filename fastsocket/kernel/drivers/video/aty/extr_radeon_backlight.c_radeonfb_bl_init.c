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
struct radeonfb_info {scalar_t__ mon1_type; scalar_t__ family; TYPE_2__* info; } ;
struct radeon_bl_privdata {int negative; struct radeonfb_info* rinfo; } ;
struct TYPE_3__ {int /*<<< orphan*/  power; scalar_t__ max_brightness; scalar_t__ brightness; } ;
struct backlight_device {TYPE_1__ props; } ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_4__ {int node; struct backlight_device* bl_dev; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ CHIP_FAMILY_RV200 ; 
 scalar_t__ CHIP_FAMILY_RV250 ; 
 scalar_t__ CHIP_FAMILY_RV280 ; 
 scalar_t__ CHIP_FAMILY_RV350 ; 
 scalar_t__ FB_BACKLIGHT_LEVELS ; 
 int FB_BACKLIGHT_MAX ; 
 int /*<<< orphan*/  FB_BLANK_UNBLANK ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct backlight_device*) ; 
 int MAX_RADEON_LEVEL ; 
 scalar_t__ MT_LCD ; 
 struct backlight_device* backlight_device_register (char*,int /*<<< orphan*/ ,struct radeon_bl_privdata*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  fb_bl_default_curve (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  kfree (struct radeon_bl_privdata*) ; 
 struct radeon_bl_privdata* kmalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ machine_is_compatible (char*) ; 
 int /*<<< orphan*/  pmac_has_backlight_type (char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 
 int /*<<< orphan*/  radeon_bl_data ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

void radeonfb_bl_init(struct radeonfb_info *rinfo)
{
	struct backlight_device *bd;
	struct radeon_bl_privdata *pdata;
	char name[12];

	if (rinfo->mon1_type != MT_LCD)
		return;

#ifdef CONFIG_PMAC_BACKLIGHT
	if (!pmac_has_backlight_type("ati") &&
	    !pmac_has_backlight_type("mnca"))
		return;
#endif

	pdata = kmalloc(sizeof(struct radeon_bl_privdata), GFP_KERNEL);
	if (!pdata) {
		printk("radeonfb: Memory allocation failed\n");
		goto error;
	}

	snprintf(name, sizeof(name), "radeonbl%d", rinfo->info->node);

	bd = backlight_device_register(name, rinfo->info->dev, pdata, &radeon_bl_data);
	if (IS_ERR(bd)) {
		rinfo->info->bl_dev = NULL;
		printk("radeonfb: Backlight registration failed\n");
		goto error;
	}

	pdata->rinfo = rinfo;

	/* Pardon me for that hack... maybe some day we can figure out in what
	 * direction backlight should work on a given panel?
	 */
	pdata->negative =
		(rinfo->family != CHIP_FAMILY_RV200 &&
		 rinfo->family != CHIP_FAMILY_RV250 &&
		 rinfo->family != CHIP_FAMILY_RV280 &&
		 rinfo->family != CHIP_FAMILY_RV350);

#ifdef CONFIG_PMAC_BACKLIGHT
	pdata->negative = pdata->negative ||
		machine_is_compatible("PowerBook4,3") ||
		machine_is_compatible("PowerBook6,3") ||
		machine_is_compatible("PowerBook6,5");
#endif

	rinfo->info->bl_dev = bd;
	fb_bl_default_curve(rinfo->info, 0,
		 63 * FB_BACKLIGHT_MAX / MAX_RADEON_LEVEL,
		217 * FB_BACKLIGHT_MAX / MAX_RADEON_LEVEL);

	bd->props.max_brightness = FB_BACKLIGHT_LEVELS - 1;
	bd->props.brightness = bd->props.max_brightness;
	bd->props.power = FB_BLANK_UNBLANK;
	backlight_update_status(bd);

	printk("radeonfb: Backlight initialized (%s)\n", name);

	return;

error:
	kfree(pdata);
	return;
}