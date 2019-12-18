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
typedef  int u32 ;
struct pmac_gpio {int addr; int active_state; int active_val; int inactive_val; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,char const*,...) ; 
 long ENODEV ; 
 struct device_node* find_audio_device (char const*) ; 
 struct device_node* find_compatible_audio_device (char const*) ; 
 long irq_of_parse_and_map (struct device_node*,int /*<<< orphan*/ ) ; 
 int* of_get_property (struct device_node*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  snd_printd (char*,char const*) ; 
 int /*<<< orphan*/  snd_printdd (char*,char const*) ; 

__attribute__((used)) static long tumbler_find_device(const char *device, const char *platform,
				struct pmac_gpio *gp, int is_compatible)
{
	struct device_node *node;
	const u32 *base;
	u32 addr;
	long ret;

	if (is_compatible)
		node = find_compatible_audio_device(device);
	else
		node = find_audio_device(device);
	if (! node) {
		DBG("(W) cannot find audio device %s !\n", device);
		snd_printdd("cannot find device %s\n", device);
		return -ENODEV;
	}

	base = of_get_property(node, "AAPL,address", NULL);
	if (! base) {
		base = of_get_property(node, "reg", NULL);
		if (!base) {
			DBG("(E) cannot find address for device %s !\n", device);
			snd_printd("cannot find address for device %s\n", device);
			of_node_put(node);
			return -ENODEV;
		}
		addr = *base;
		if (addr < 0x50)
			addr += 0x50;
	} else
		addr = *base;

	gp->addr = addr & 0x0000ffff;
	/* Try to find the active state, default to 0 ! */
	base = of_get_property(node, "audio-gpio-active-state", NULL);
	if (base) {
		gp->active_state = *base;
		gp->active_val = (*base) ? 0x5 : 0x4;
		gp->inactive_val = (*base) ? 0x4 : 0x5;
	} else {
		const u32 *prop = NULL;
		gp->active_state = 0;
		gp->active_val = 0x4;
		gp->inactive_val = 0x5;
		/* Here are some crude hacks to extract the GPIO polarity and
		 * open collector informations out of the do-platform script
		 * as we don't yet have an interpreter for these things
		 */
		if (platform)
			prop = of_get_property(node, platform, NULL);
		if (prop) {
			if (prop[3] == 0x9 && prop[4] == 0x9) {
				gp->active_val = 0xd;
				gp->inactive_val = 0xc;
			}
			if (prop[3] == 0x1 && prop[4] == 0x1) {
				gp->active_val = 0x5;
				gp->inactive_val = 0x4;
			}
		}
	}

	DBG("(I) GPIO device %s found, offset: %x, active state: %d !\n",
	    device, gp->addr, gp->active_state);

	ret = irq_of_parse_and_map(node, 0);
	of_node_put(node);
	return ret;
}