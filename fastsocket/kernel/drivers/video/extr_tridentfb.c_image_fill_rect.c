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
struct tridentfb_par {int dummy; } ;

/* Variables and functions */
 int DST1 ; 
 int DST2 ; 
 int ROP_S ; 
 int point (int,int) ; 
 int /*<<< orphan*/  writemmr (struct tridentfb_par*,int,int) ; 

__attribute__((used)) static void image_fill_rect(struct tridentfb_par *par,
			    u32 x, u32 y, u32 w, u32 h, u32 c, u32 rop)
{
	writemmr(par, 0x2120, 0x80000000);
	writemmr(par, 0x2120, 0x90000000 | ROP_S);

	writemmr(par, 0x2144, c);

	writemmr(par, DST1, point(x, y));
	writemmr(par, DST2, point(x + w - 1, y + h - 1));

	writemmr(par, 0x2124, 0x80000000 | 3 << 22 | 1 << 10 | 1 << 9);
}