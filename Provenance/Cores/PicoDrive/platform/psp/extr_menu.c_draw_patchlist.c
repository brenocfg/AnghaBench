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
struct TYPE_2__ {int active; char* name; } ;

/* Variables and functions */
 int PicoPatchCount ; 
 TYPE_1__* PicoPatches ; 
 int /*<<< orphan*/  menu_draw_begin () ; 
 int /*<<< orphan*/  menu_draw_end () ; 
 int /*<<< orphan*/  smalltext_out16_lim (int,int,char*,int,int) ; 
 int /*<<< orphan*/  text_out16 (int,int,char*) ; 

__attribute__((used)) static void draw_patchlist(int sel)
{
	int start, i, pos, active;

	start = 13 - sel;

	menu_draw_begin();

	for (i = 0; i < PicoPatchCount; i++) {
		pos = start + i;
		if (pos < 0)  continue;
		if (pos > 26) break;
		active = PicoPatches[i].active;
		smalltext_out16_lim(14,     pos*10, active ? "ON " : "OFF", active ? 0xfff6 : 0xffff, 3);
		smalltext_out16_lim(14+6*4, pos*10, PicoPatches[i].name, active ? 0xfff6 : 0xffff, 53-6);
	}
	pos = start + i;
	if (pos < 27) smalltext_out16_lim(14, pos*10, "done", 0xffff, 4);

	text_out16(5, 130, ">");
	menu_draw_end();
}