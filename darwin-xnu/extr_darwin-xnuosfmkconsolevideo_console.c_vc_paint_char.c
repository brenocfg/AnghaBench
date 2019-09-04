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
struct TYPE_2__ {int v_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  vc_paint_char_16 (unsigned int,unsigned int,unsigned char,int,unsigned char,int) ; 
 int /*<<< orphan*/  vc_paint_char_32 (unsigned int,unsigned int,unsigned char,int,unsigned char,int) ; 
 int /*<<< orphan*/  vc_paint_char_8 (unsigned int,unsigned int,unsigned char,int,unsigned char,int) ; 
 TYPE_1__ vinfo ; 

__attribute__((used)) static void
vc_paint_char(unsigned int xx, unsigned int yy, unsigned char ch, int attrs,
	      unsigned char ch_previous, int attrs_previous)
{
	if(!vinfo.v_depth)
		return;

	switch(vinfo.v_depth) {
	case 8:
		vc_paint_char_8(xx, yy, ch, attrs, ch_previous, attrs_previous);
		break;
	case 16:
		vc_paint_char_16(xx, yy, ch, attrs, ch_previous,
				 attrs_previous);
		break;
	case 30:
	case 32:
		vc_paint_char_32(xx, yy, ch, attrs, ch_previous,
				 attrs_previous);
		break;
	}
}