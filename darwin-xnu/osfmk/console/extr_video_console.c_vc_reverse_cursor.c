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
struct TYPE_2__ {unsigned int v_depth; unsigned int v_rowbytes; scalar_t__ v_baseaddr; } ;

/* Variables and functions */
 unsigned int ISO_CHAR_HEIGHT ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void
vc_reverse_cursor(unsigned int xx, unsigned int yy)
{
	uint32_t *where;
	int line, col;

	if(!vinfo.v_depth)
		return;

	where = (uint32_t*)(vinfo.v_baseaddr + 
			(yy * ISO_CHAR_HEIGHT * vinfo.v_rowbytes) + 
			(xx /** ISO_CHAR_WIDTH*/ * vinfo.v_depth));
	for (line = 0; line < ISO_CHAR_HEIGHT; line++) {
		switch (vinfo.v_depth) {
			case 8:
				where[0] = ~where[0];
				where[1] = ~where[1];
				break;
			case 16:
				for (col = 0; col < 4; col++)
					where[col] = ~where[col];
				break;
			case 32:
				for (col = 0; col < 8; col++)
					where[col] = ~where[col];
				break;
		}
		where = (uint32_t*)(((unsigned char*)where)+vinfo.v_rowbytes);
	}
}