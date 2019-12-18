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

/* Variables and functions */

__attribute__((used)) static int volconvert(int level)
{
	level >>= 14;		/* Map 16bits down to 2 bit */
	level &= 3;

	/* convert to card-friendly values */
	switch (level) {
	case 0:
		return 0;
	case 1:
		return 1;
	case 2:
		return 4;
	case 3:
		return 5;
	}
	return 0;	/* Quieten gcc */
}