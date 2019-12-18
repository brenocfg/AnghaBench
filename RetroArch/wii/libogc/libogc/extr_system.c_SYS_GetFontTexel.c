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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
typedef  int s32 ;
struct TYPE_2__ {int first_char; int last_char; int inval_char; int sheet_column; int cell_width; int cell_height; int sheet_size; int sheet_width; } ;

/* Variables and functions */
 int sys_fontcharsinsheet ; 
 TYPE_1__* sys_fontdata ; 
 int /*<<< orphan*/ * sys_fontimage ; 
 int* sys_fontwidthtab ; 

void SYS_GetFontTexel(s32 c,void *image,s32 pos,s32 stride,s32 *width)
{
	u32 sheets,rem;
	u32 xoff,yoff;
	u32 xpos,ypos;
	u8 *img_start;
	u8 *ptr1,*ptr2;

	if(!sys_fontwidthtab || ! sys_fontimage) return;

	if(c<sys_fontdata->first_char || c>sys_fontdata->last_char) c = sys_fontdata->inval_char;
	else c -= sys_fontdata->first_char;

	sheets = c/sys_fontcharsinsheet;
	rem = c%sys_fontcharsinsheet;
	xoff = (rem%sys_fontdata->sheet_column)*sys_fontdata->cell_width;
	yoff = (rem/sys_fontdata->sheet_column)*sys_fontdata->cell_height;
	img_start = sys_fontimage+(sys_fontdata->sheet_size*sheets);

	ypos = 0;
	while(ypos<sys_fontdata->cell_height) {
		xpos = 0;
		while(xpos<sys_fontdata->cell_width) {
			ptr1 = img_start+(((sys_fontdata->sheet_width/8)<<5)*((ypos+yoff)/8));
			ptr1 = ptr1+(((xpos+xoff)/8)<<5);
			ptr1 = ptr1+(((ypos+yoff)%8)<<2);
			ptr1 = ptr1+(((xpos+xoff)%8)/2);

			ptr2 = image+((ypos/8)*(((stride<<1)/8)<<5));
			ptr2 = ptr2+(((xpos+pos)/8)<<5);
			ptr2 = ptr2+(((xpos+pos)%8)/2);
			ptr2 = ptr2+((ypos%8)<<2);

			*ptr2 = *ptr1;

			xpos += 2;
		}
		ypos++;
	}
	*width = sys_fontwidthtab[c];
}