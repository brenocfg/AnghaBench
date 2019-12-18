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

int scale_precondition(unsigned scale, unsigned pixel, unsigned width, unsigned height)
{
	if (scale != 2 && scale != 3 && scale != 4)
		return -1;

	if (pixel != 1 && pixel != 2 && pixel != 4)
		return -1;

	switch (scale) {
	case 2 :
	case 3 :
		if (height < 2)
			return -1;
		break;
	case 4 :
		if (height < 4)
			return -1;
		break;
	}

#if defined(__GNUC__) && defined(__i386__)
	switch (scale) {
	case 2 :
	case 4 :
		if (width < (16 / pixel))
			return -1;
		if (width % (8 / pixel) != 0)
			return -1;
		break;
	case 3 :
		if (width < 2)
			return -1;
		break;
	}
#else
	if (width < 2)
		return -1;
#endif

	return 0;
}