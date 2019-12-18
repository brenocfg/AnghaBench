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
 int /*<<< orphan*/  CMD ; 
 int /*<<< orphan*/  COLOR ; 
 int /*<<< orphan*/  DST1 ; 
 int /*<<< orphan*/  DST2 ; 
 int /*<<< orphan*/  ROP ; 
 int ROP_S ; 
 int ROP_X ; 
 int point (int,int) ; 
 int /*<<< orphan*/  writemmr (struct tridentfb_par*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void blade_fill_rect(struct tridentfb_par *par,
			    u32 x, u32 y, u32 w, u32 h, u32 c, u32 rop)
{
	writemmr(par, COLOR, c);
	writemmr(par, ROP, rop ? ROP_X : ROP_S);
	writemmr(par, CMD, 0x20000000 | 1 << 19 | 1 << 4 | 2 << 2);

	writemmr(par, DST1, point(x, y));
	writemmr(par, DST2, point(x + w - 1, y + h - 1));
}