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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_2__ {int v_rowbytes; int v_rowscanbytes; unsigned int v_rows; int v_height; scalar_t__ v_baseaddr; int /*<<< orphan*/  v_depth; } ;

/* Variables and functions */
 int ISO_CHAR_HEIGHT ; 
 int /*<<< orphan*/  gc_clear_line (unsigned int,unsigned int,int) ; 
 int /*<<< orphan*/  vc_color_back ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void 
vc_clear_screen(unsigned int xx, unsigned int yy, unsigned int scrreg_top,
		unsigned int scrreg_bottom, int which)
{
	uint32_t *p, *endp, *row;
	int      linelongs, col;
	int      rowline, rowlongs;

	if(!vinfo.v_depth)
		return;

	linelongs = vinfo.v_rowbytes * (ISO_CHAR_HEIGHT >> 2);
	rowline = vinfo.v_rowscanbytes >> 2;
	rowlongs = vinfo.v_rowbytes >> 2;

	p = (uint32_t*) vinfo.v_baseaddr;
	endp = (uint32_t*) vinfo.v_baseaddr;

	switch (which) {
	case 0:		/* To end of screen	 */
		gc_clear_line(xx, yy, 0);
		if (yy < scrreg_bottom - 1) {
			p += (yy + 1) * linelongs;
			endp += scrreg_bottom * linelongs;
		}
		break;
	case 1:		/* To start of screen	 */
		gc_clear_line(xx, yy, 1);
		if (yy > scrreg_top) {
			p += scrreg_top * linelongs;
			endp += yy * linelongs;
		}
		break;
	case 2:		/* Whole screen		 */
		p += scrreg_top * linelongs;
		if (scrreg_bottom == vinfo.v_rows) {
			endp += rowlongs * vinfo.v_height;
		} else {
			endp += scrreg_bottom * linelongs;
		}
		break;
	}

	for (row = p ; row < endp ; row += rowlongs) {
		for (col = 0; col < rowline; col++) 
			*(row+col) = vc_color_back;
	}
}