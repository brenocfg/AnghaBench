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
struct tridentfb_par {scalar_t__ io_virt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BGCOLOR ; 
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  COLOR ; 
 int /*<<< orphan*/  DST1 ; 
 int /*<<< orphan*/  DST2 ; 
 int /*<<< orphan*/  memcpy (scalar_t__,char const*,int) ; 
 int point (int,int) ; 
 int /*<<< orphan*/  writemmr (struct tridentfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void blade_image_blit(struct tridentfb_par *par, const char *data,
			     u32 x, u32 y, u32 w, u32 h, u32 c, u32 b)
{
	unsigned size = ((w + 31) >> 5) * h;

	writemmr(par, COLOR, c);
	writemmr(par, BGCOLOR, b);
	writemmr(par, CMD, 0xa0000000 | 3 << 19);

	writemmr(par, DST1, point(x, y));
	writemmr(par, DST2, point(x + w - 1, y + h - 1));

	memcpy(par->io_virt + 0x10000, data, 4 * size);
}