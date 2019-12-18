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
typedef  int u_long ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct fb_info {scalar_t__ screen_base; } ;

/* Variables and functions */
 int BPL ; 
 int /*<<< orphan*/  expand16_2col2mask (int,int,int*,int*) ; 
 int /*<<< orphan*/  fill8_2col (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/  const) ; 

void atafb_iplan2p2_linefill(struct fb_info *info, u_long next_line,
                             int dy, int dx, u32 width,
                             const u8 *data, u32 bgcolor, u32 fgcolor)
{
	u32 *dest;
	const u16 *data16;
	int rows;
	u32 fgm[4], bgm[4], m;

	dest = (u32 *)(info->screen_base + dy * next_line + (dx & ~15) / (8 / BPL));
	if (dx & 15) {
		fill8_2col((u8 *)dest + 1, fgcolor, bgcolor, *data++);
		dest += BPL / 2;
		width -= 8;
	}

	if (width >= 16) {
		data16 = (const u16 *)data;
		expand16_2col2mask(fgcolor, bgcolor, fgm, bgm);

		for (rows = width / 16; rows; rows--) {
			u16 d = *data16++;
			m = d | ((u32)d << 16);
			*dest++ = (m & fgm[0]) ^ bgm[0];
		}

		data = (const u8 *)data16;
		width &= 15;
	}

	if (width)
		fill8_2col((u8 *)dest, fgcolor, bgcolor, *data);
}