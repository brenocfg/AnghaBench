#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct TYPE_3__ {int sheet_image; int first_char; int last_char; int inval_char; int width_table; int cell_height; int cell_width; } ;
typedef  TYPE_1__ sys_fontheader ;

/* Variables and functions */
 int /*<<< orphan*/  __SYS_ReadROM (void*,int,int) ; 
 int /*<<< orphan*/  decode_szp (void*,void*) ; 
 int /*<<< orphan*/  expand_font (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fheight ; 
 TYPE_1__* fontHeader ; 
 int /*<<< orphan*/ * fontImage ; 
 void* fontTexture ; 
 int /*<<< orphan*/ * font_size ; 
 int /*<<< orphan*/  free (void*) ; 
 void* ipl_fontarea ; 
 int /*<<< orphan*/  ipl_set_config (int) ; 
 void* memalign (int,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

int FONT_Init(void)
{
#ifndef HW_RVL
  /* --- Game Cube --- disable Qoob before accessing IPL */
  ipl_set_config(6);
#endif

  /* read IPL font (ASCII) from Mask ROM */
  ipl_fontarea = memalign(32,131360);
  if (!ipl_fontarea)
    return 0;
  memset(ipl_fontarea,0,131360);
  __SYS_ReadROM(ipl_fontarea+119072,12288,0x1FCF00);

  /* YAY0 decompression */
  decode_szp(ipl_fontarea+119072,ipl_fontarea);

	/* retrieve IPL font data */
  fontHeader = (sys_fontheader*)ipl_fontarea;
  fontImage = (u8*)((((u32)ipl_fontarea+fontHeader->sheet_image)+31)&~31);
  
  /* expand to I4 format */
  expand_font((u8*)ipl_fontarea+fontHeader->sheet_image,fontImage);

  /* character width table */
  int i,c;
  for (i=0; i<256; ++i)
  {
    if ((i < fontHeader->first_char) || (i > fontHeader->last_char))
      c = fontHeader->inval_char;
    else
      c = i - fontHeader->first_char;

    font_size[i] = ((u8*)fontHeader)[fontHeader->width_table + c];
  }

  /* font height */
  fheight = fontHeader->cell_height;

  /* initialize texture data */
  fontTexture = memalign(32, fontHeader->cell_width * fontHeader->cell_height / 2);
  if (!fontTexture)
  {
    free(ipl_fontarea);
    return 0;
  }

  return 1;
}