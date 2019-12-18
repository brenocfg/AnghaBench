#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int CMDPMOD; } ;
typedef  TYPE_1__ vdp1cmd_struct ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
typedef  int /*<<< orphan*/ * iPix ;
typedef  int /*<<< orphan*/  Vdp1 ;
struct TYPE_6__ {scalar_t__ b; scalar_t__ g; scalar_t__ r; } ;

/* Variables and functions */
 int COLOR (int,int,int) ; 
 scalar_t__ CheckDil (int,int /*<<< orphan*/ *) ; 
 scalar_t__ IsClipped (int,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int alphablend16 (int,int,int) ; 
 int currentPixel ; 
 int currentPixelIsVisible ; 
 int gouraudAdjust (int,int) ; 
 TYPE_3__ leftColumnColor ; 
 int vdp1interlace ; 
 int vdp1width ; 

__attribute__((used)) static void putpixel(int x, int y, Vdp1* regs, vdp1cmd_struct * cmd, u8 * back_framebuffer) {

	u16* iPix;
	int mesh = cmd->CMDPMOD & 0x0100;
	int SPD = ((cmd->CMDPMOD & 0x40) != 0);//show the actual color of transparent pixels if 1 (they won't be drawn transparent)
   int original_y = y;

   if (CheckDil(y, regs))
      return;

	y /= vdp1interlace;
   iPix = &((u16 *)back_framebuffer)[(y * vdp1width) + x];

   if (iPix >= (u16*)(back_framebuffer + 0x40000))
		return;

	if(mesh && (x^y)&1)
		return;

   if (IsClipped(x, original_y, regs, cmd))
      return;

	if (cmd->CMDPMOD & (1 << 15))
	{
		if (currentPixel) {
			*iPix |= 0x8000;
			return;
		}
	}

	if ( SPD || (currentPixel & currentPixelIsVisible))
	{
		switch( cmd->CMDPMOD & 0x7 )//we want bits 0,1,2
		{
		case 0:	// replace
			if (!((currentPixel == 0) && !SPD))
				*(iPix) = currentPixel;
			break;
		case 1: // shadow
			if (*(iPix) & (1 << 15)) // only if MSB of framebuffer data is set
				*(iPix) = alphablend16(*(iPix), 0, (1 << 7)) | (1 << 15);
			break;
		case 2: // half luminance
			*(iPix) = ((currentPixel & ~0x8421) >> 1) | (1 << 15);
			break;
		case 3: // half transparent
			if ( *(iPix) & (1 << 15) )//only if MSB of framebuffer data is set
				*(iPix) = alphablend16( *(iPix), currentPixel, (1 << 7) ) | (1 << 15);
			else
				*(iPix) = currentPixel;
			break;
		case 4: //gouraud
			#define COLOR(r,g,b)    (((r)&0x1F)|(((g)&0x1F)<<5)|(((b)&0x1F)<<10) |0x8000 )

			//handle the special case demonstrated in the sgl chrome demo
			//if we are in a paletted bank mode and the other two colors are unused, adjust the index value instead of rgb
			if(
				(((cmd->CMDPMOD >> 3) & 0x7) != 5) &&
				(((cmd->CMDPMOD >> 3) & 0x7) != 1) &&
				(int)leftColumnColor.g == 16 &&
				(int)leftColumnColor.b == 16)
			{
				int c = (int)(leftColumnColor.r-0x10);
				if(c < 0) c = 0;
				currentPixel = currentPixel+c;
				*(iPix) = currentPixel;
				break;
			}
			*(iPix) = COLOR(
				gouraudAdjust(
				currentPixel&0x001F,
				(int)leftColumnColor.r),

				gouraudAdjust(
				(currentPixel&0x03e0) >> 5,
				(int)leftColumnColor.g),

				gouraudAdjust(
				(currentPixel&0x7c00) >> 10,
				(int)leftColumnColor.b)
				);
			break;
		default:
			*(iPix) = alphablend16( COLOR((int)leftColumnColor.r,(int)leftColumnColor.g, (int)leftColumnColor.b), currentPixel, (1 << 7) ) | (1 << 15);
			break;
		}
	}
}