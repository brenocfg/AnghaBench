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
struct TYPE_3__ {int width; size_t rows; unsigned char* buffer; int /*<<< orphan*/  pitch; } ;
typedef  size_t FT_Int ;
typedef  TYPE_1__ FT_Bitmap ;

/* Variables and functions */
 size_t HEIGHT ; 
 size_t WIDTH ; 
 unsigned char* image ; 
 unsigned char* pixelData ; 

void
draw_bitmap( FT_Bitmap*  bitmap,
             FT_Int      x,
             FT_Int      y)
{
  FT_Int  i, j, p, q;
  FT_Int  x_max = x + bitmap->width;
  FT_Int  y_max = y + bitmap->rows;
  int xbyte;
  int xbit;
  unsigned char* pcur;

  unsigned char* src = bitmap->buffer;
  unsigned char* dest = pixelData;

  // Note: FT_RENDER_MONO_MODE render characater's one pixel by a single bit,
  // translate the single bit to a single char for displaying image.
  for(int _y = 0; _y < bitmap->rows; ++_y)
  {
	  for(int _x = 0; _x < bitmap->width; ++_x)
	  {	
		  xbyte = _x / 8;
		  xbit = _x - xbyte * 8;
		  pcur = dest + _x;

		  // test if the pixel bit be set
		  if(src[xbyte] & (0x80 >> xbit))
		  {
			  *pcur = 0xFF;
		  }
		  else
		  {
			  *pcur = 0;
		  }
	  }
	  src += bitmap->pitch;
	  dest += bitmap->width;
  }

  // display the character to ref txt file
  for ( i = x, p = 0; i < x_max; i++, p++ )
  {
    for ( j = y, q = 0; j < y_max; j++, q++ )
    {
      if ( i < 0      || j < 0       ||
           i >= WIDTH || j >= HEIGHT )
        continue;
		
      image[j*WIDTH + i] |= pixelData[q * bitmap->width + p];
    }
  }
}