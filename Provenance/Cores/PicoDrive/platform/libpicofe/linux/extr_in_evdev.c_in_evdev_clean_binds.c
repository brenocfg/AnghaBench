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
typedef  int /*<<< orphan*/  keybits ;
struct TYPE_2__ {scalar_t__ abs_lzone; scalar_t__ abs_to_digital; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ in_evdev_t ;

/* Variables and functions */
 int /*<<< orphan*/  EVIOCGBIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EV_KEY ; 
 int IN_BINDTYPE_COUNT ; 
 int IN_BIND_OFFS (int,int) ; 
 int /*<<< orphan*/  KEYBITS_BIT (int) ; 
 int /*<<< orphan*/  KEYBITS_BIT_SET (int /*<<< orphan*/ ) ; 
 int KEY_CNT ; 
 int /*<<< orphan*/  KEY_DOWN ; 
 int /*<<< orphan*/  KEY_LEFT ; 
 int /*<<< orphan*/  KEY_RIGHT ; 
 int /*<<< orphan*/  KEY_UP ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  perror (char*) ; 

__attribute__((used)) static int in_evdev_clean_binds(void *drv_data, int *binds, int *def_binds)
{
	int keybits[KEY_CNT / sizeof(int)];
	in_evdev_t *dev = drv_data;
	int i, t, ret, offs, count = 0;

	memset(keybits, 0, sizeof(keybits));
	ret = ioctl(dev->fd, EVIOCGBIT(EV_KEY, sizeof(keybits)), keybits);
	if (ret == -1) {
		perror("in_evdev: ioctl failed");
		// memset(keybits, 0xff, sizeof(keybits)); /* mark all as good */
	}

	if (dev->abs_to_digital && dev->abs_lzone != 0) {
		KEYBITS_BIT_SET(KEY_LEFT);
		KEYBITS_BIT_SET(KEY_RIGHT);
		KEYBITS_BIT_SET(KEY_UP);
		KEYBITS_BIT_SET(KEY_DOWN);
	}

	for (i = 0; i < KEY_CNT; i++) {
		for (t = 0; t < IN_BINDTYPE_COUNT; t++) {
			offs = IN_BIND_OFFS(i, t);
			if (!KEYBITS_BIT(i))
				binds[offs] = def_binds[offs] = 0;
			if (binds[offs])
				count++;
		}
	}

	return count;
}