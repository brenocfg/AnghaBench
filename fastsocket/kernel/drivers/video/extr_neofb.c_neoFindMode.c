#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int x_res; int mode; int y_res; } ;
typedef  TYPE_1__ biosMode ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* bios16 ; 
 TYPE_1__* bios24 ; 
 TYPE_1__* bios32 ; 
 TYPE_1__* bios8 ; 

__attribute__((used)) static int neoFindMode(int xres, int yres, int depth)
{
	int xres_s;
	int i, size;
	biosMode *mode;

	switch (depth) {
	case 8:
		size = ARRAY_SIZE(bios8);
		mode = bios8;
		break;
	case 16:
		size = ARRAY_SIZE(bios16);
		mode = bios16;
		break;
	case 24:
		size = ARRAY_SIZE(bios24);
		mode = bios24;
		break;
#ifdef NO_32BIT_SUPPORT_YET
	case 32:
		size = ARRAY_SIZE(bios32);
		mode = bios32;
		break;
#endif
	default:
		return 0;
	}

	for (i = 0; i < size; i++) {
		if (xres <= mode[i].x_res) {
			xres_s = mode[i].x_res;
			for (; i < size; i++) {
				if (mode[i].x_res != xres_s)
					return mode[i - 1].mode;
				if (yres <= mode[i].y_res)
					return mode[i].mode;
			}
		}
	}
	return mode[size - 1].mode;
}