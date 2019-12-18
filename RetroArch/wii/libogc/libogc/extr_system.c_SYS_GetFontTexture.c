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
typedef  int u32 ;
typedef  size_t s32 ;
struct TYPE_2__ {size_t first_char; size_t last_char; size_t inval_char; int sheet_size; int sheet_column; int cell_width; int cell_height; } ;

/* Variables and functions */
 size_t sys_fontcharsinsheet ; 
 TYPE_1__* sys_fontdata ; 
 void* sys_fontimage ; 
 size_t* sys_fontwidthtab ; 

void SYS_GetFontTexture(s32 c,void **image,s32 *xpos,s32 *ypos,s32 *width)
{
	u32 sheets,rem;

	*xpos = 0;
	*ypos = 0;
	*image = NULL;
	if(!sys_fontwidthtab || ! sys_fontimage) return;

	if(c<sys_fontdata->first_char || c>sys_fontdata->last_char) c = sys_fontdata->inval_char;
	else c -= sys_fontdata->first_char;

	sheets = c/sys_fontcharsinsheet;
	rem = c%sys_fontcharsinsheet;
	*image = sys_fontimage+(sys_fontdata->sheet_size*sheets);
	*xpos = (rem%sys_fontdata->sheet_column)*sys_fontdata->cell_width;
	*ypos = (rem/sys_fontdata->sheet_column)*sys_fontdata->cell_height;
	*width = sys_fontwidthtab[c];
}