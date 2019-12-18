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
typedef  int u8 ;
typedef  int u32 ;
struct b43_c32 {int i; int q; } ;
typedef  int s8 ;
typedef  void* s32 ;

/* Variables and functions */

struct b43_c32 b43_cordic(int theta)
{
	static const u32 arctg[] = {
		2949120, 1740967, 919879, 466945, 234379, 117304,
		  58666,   29335,  14668,   7334,   3667,   1833,
		    917,     458,    229,    115,     57,     29,
	};
	u8 i;
	s32 tmp;
	s8 signx = 1;
	u32 angle = 0;
	struct b43_c32 ret = { .i = 39797, .q = 0, };

	while (theta > (180 << 16))
		theta -= (360 << 16);
	while (theta < -(180 << 16))
		theta += (360 << 16);

	if (theta > (90 << 16)) {
		theta -= (180 << 16);
		signx = -1;
	} else if (theta < -(90 << 16)) {
		theta += (180 << 16);
		signx = -1;
	}

	for (i = 0; i <= 17; i++) {
		if (theta > angle) {
			tmp = ret.i - (ret.q >> i);
			ret.q += ret.i >> i;
			ret.i = tmp;
			angle += arctg[i];
		} else {
			tmp = ret.i + (ret.q >> i);
			ret.q -= ret.i >> i;
			ret.i = tmp;
			angle -= arctg[i];
		}
	}

	ret.i *= signx;
	ret.q *= signx;

	return ret;
}