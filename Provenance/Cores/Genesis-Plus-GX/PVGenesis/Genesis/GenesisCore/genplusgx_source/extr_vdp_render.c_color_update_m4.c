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

/* Variables and functions */
 unsigned int MAKE_PIXEL (int,int,int) ; 
#define  SYSTEM_GG 129 
 int SYSTEM_GGMS ; 
 int SYSTEM_MD ; 
#define  SYSTEM_SG 128 
 unsigned int* pixel ; 
 unsigned int* pixel_lut_m4 ; 
 int* reg ; 
 int system_hw ; 
 unsigned int* tms_crom ; 
 unsigned int* tms_palette ; 

void color_update_m4(int index, unsigned int data)
{
  switch (system_hw)
  {
    case SYSTEM_GG:
    {
      /* CRAM value (BBBBGGGGRRRR) */
      int r = (data >> 0) & 0x0F;
      int g = (data >> 4) & 0x0F;
      int b = (data >> 8) & 0x0F;

      /* Convert to output pixel */
      data = MAKE_PIXEL(r,g,b);
      break;
    }

    case SYSTEM_SG:
    {
      /* Fixed TMS9918 palette */
      if (index & 0x0F)
      {
        /* Colors 1-15 */
        data = tms_palette[index & 0x0F];
      }
      else
      {
        /* Backdrop color */
        data = tms_palette[reg[7] & 0x0F];
      }
      break;
    }

    default:
    {
      /* Test M4 bit */
      if (!(reg[0] & 0x04))
      {
        if (system_hw & SYSTEM_MD)
        {
          /* Invalid Mode (black screen) */
          data = 0x00;
        }
        else if (system_hw != SYSTEM_GGMS)
        {
          /* Fixed CRAM palette */
          if (index & 0x0F)
          {
            /* Colors 1-15 */
            data = tms_crom[index & 0x0F];
          }
          else
          {
            /* Backdrop color */
            data = tms_crom[reg[7] & 0x0F];
          }
        }
      }

      /* Mode 4 palette */
      data = pixel_lut_m4[data & 0x3F];
      break;
    }
  }


  /* Input pixel: x0xiiiii (normal) or 01000000 (backdrop) */
  if (reg[0] & 0x04)
  {
    /* Mode 4 */
    pixel[0x00 | index] = data;
    pixel[0x20 | index] = data;
    pixel[0x80 | index] = data;
    pixel[0xA0 | index] = data;
  }
  else
  {
    /* TMS9918 modes (palette bit forced to 1 because Game Gear uses CRAM palette #1) */
    if ((index == 0x40) || (index == (0x10 | (reg[7] & 0x0F))))
    {
      /* Update backdrop color */
      pixel[0x40] = data;

      /* Update transparent color */
      pixel[0x10] = data;
      pixel[0x30] = data;
      pixel[0x90] = data;
      pixel[0xB0] = data;
    }

    if (index & 0x0F)
    {
      /* update non-transparent colors */
      pixel[0x00 | index] = data;
      pixel[0x20 | index] = data;
      pixel[0x80 | index] = data;
      pixel[0xA0 | index] = data;
    }
  }
}