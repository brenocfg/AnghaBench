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
typedef  int /*<<< orphan*/  u16 ;
struct wm8350 {int (* read_dev ) (struct wm8350*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ;int /*<<< orphan*/ * reg_cache; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  readable; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int WM8350_AIF_TEST ; 
 int WM8350_CLOCK_CONTROL_1 ; 
 int WM8350_MAX_REGISTER ; 
 int /*<<< orphan*/  be16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int stub1 (struct wm8350*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * wm8350_mode0_defaults ; 
 int /*<<< orphan*/ * wm8350_mode1_defaults ; 
 int /*<<< orphan*/ * wm8350_mode2_defaults ; 
 int /*<<< orphan*/ * wm8350_mode3_defaults ; 
 TYPE_1__* wm8350_reg_io_map ; 
 int /*<<< orphan*/ * wm8351_mode0_defaults ; 
 int /*<<< orphan*/ * wm8351_mode1_defaults ; 
 int /*<<< orphan*/ * wm8351_mode2_defaults ; 
 int /*<<< orphan*/ * wm8351_mode3_defaults ; 
 int /*<<< orphan*/ * wm8352_mode0_defaults ; 
 int /*<<< orphan*/ * wm8352_mode1_defaults ; 
 int /*<<< orphan*/ * wm8352_mode2_defaults ; 
 int /*<<< orphan*/ * wm8352_mode3_defaults ; 

__attribute__((used)) static int wm8350_create_cache(struct wm8350 *wm8350, int type, int mode)
{
	int i, ret = 0;
	u16 value;
	const u16 *reg_map;

	switch (type) {
	case 0:
		switch (mode) {
#ifdef CONFIG_MFD_WM8350_CONFIG_MODE_0
		case 0:
			reg_map = wm8350_mode0_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8350_CONFIG_MODE_1
		case 1:
			reg_map = wm8350_mode1_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8350_CONFIG_MODE_2
		case 2:
			reg_map = wm8350_mode2_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8350_CONFIG_MODE_3
		case 3:
			reg_map = wm8350_mode3_defaults;
			break;
#endif
		default:
			dev_err(wm8350->dev,
				"WM8350 configuration mode %d not supported\n",
				mode);
			return -EINVAL;
		}
		break;

	case 1:
		switch (mode) {
#ifdef CONFIG_MFD_WM8351_CONFIG_MODE_0
		case 0:
			reg_map = wm8351_mode0_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8351_CONFIG_MODE_1
		case 1:
			reg_map = wm8351_mode1_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8351_CONFIG_MODE_2
		case 2:
			reg_map = wm8351_mode2_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8351_CONFIG_MODE_3
		case 3:
			reg_map = wm8351_mode3_defaults;
			break;
#endif
		default:
			dev_err(wm8350->dev,
				"WM8351 configuration mode %d not supported\n",
				mode);
			return -EINVAL;
		}
		break;

	case 2:
		switch (mode) {
#ifdef CONFIG_MFD_WM8352_CONFIG_MODE_0
		case 0:
			reg_map = wm8352_mode0_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8352_CONFIG_MODE_1
		case 1:
			reg_map = wm8352_mode1_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8352_CONFIG_MODE_2
		case 2:
			reg_map = wm8352_mode2_defaults;
			break;
#endif
#ifdef CONFIG_MFD_WM8352_CONFIG_MODE_3
		case 3:
			reg_map = wm8352_mode3_defaults;
			break;
#endif
		default:
			dev_err(wm8350->dev,
				"WM8352 configuration mode %d not supported\n",
				mode);
			return -EINVAL;
		}
		break;

	default:
		dev_err(wm8350->dev,
			"WM835x configuration mode %d not supported\n",
			mode);
		return -EINVAL;
	}

	wm8350->reg_cache =
		kmalloc(sizeof(u16) * (WM8350_MAX_REGISTER + 1), GFP_KERNEL);
	if (wm8350->reg_cache == NULL)
		return -ENOMEM;

	/* Read the initial cache state back from the device - this is
	 * a PMIC so the device many not be in a virgin state and we
	 * can't rely on the silicon values.
	 */
	ret = wm8350->read_dev(wm8350, 0,
			       sizeof(u16) * (WM8350_MAX_REGISTER + 1),
			       wm8350->reg_cache);
	if (ret < 0) {
		dev_err(wm8350->dev,
			"failed to read initial cache values\n");
		goto out;
	}

	/* Mask out uncacheable/unreadable bits and the audio. */
	for (i = 0; i < WM8350_MAX_REGISTER; i++) {
		if (wm8350_reg_io_map[i].readable &&
		    (i < WM8350_CLOCK_CONTROL_1 || i > WM8350_AIF_TEST)) {
			value = be16_to_cpu(wm8350->reg_cache[i]);
			value &= wm8350_reg_io_map[i].readable;
			wm8350->reg_cache[i] = value;
		} else
			wm8350->reg_cache[i] = reg_map[i];
	}

out:
	return ret;
}