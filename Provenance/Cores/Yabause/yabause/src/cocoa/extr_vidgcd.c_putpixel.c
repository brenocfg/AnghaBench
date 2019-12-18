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
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
typedef  int /*<<< orphan*/ * iPix ;
struct TYPE_6__ {int CMDPMOD; int CMDCTRL; } ;
struct TYPE_5__ {scalar_t__ b; scalar_t__ g; scalar_t__ r; } ;
struct TYPE_4__ {int* priosused; size_t* prioritytable; } ;

/* Variables and functions */
 int COLOR (int,int,int) ; 
 int /*<<< orphan*/  PopUserClipping () ; 
 int /*<<< orphan*/  PushUserClipping (int) ; 
 int /*<<< orphan*/  Vdp1ProcessSpritePixel (int /*<<< orphan*/ ,int*,int*,int*,int*) ; 
 int alphablend16 (int,int,int) ; 
 TYPE_3__ cmd ; 
 int currentPixel ; 
 int currentPixelIsVisible ; 
 int gouraudAdjust (int,int) ; 
 TYPE_2__ leftColumnColor ; 
 scalar_t__ vdp1backframebuffer ; 
 int vdp1clipxend ; 
 int vdp1clipxstart ; 
 int vdp1clipyend ; 
 int vdp1clipystart ; 
 TYPE_1__ vdp1draw_info ; 
 int /*<<< orphan*/  vdp1spritetype ; 
 int vdp1width ; 

__attribute__((used)) static void putpixel(int x, int y) {

	u16* iPix = &((u16 *)vdp1backframebuffer)[(y * vdp1width) + x];
	int mesh = cmd.CMDPMOD & 0x0100;
	int SPD = ((cmd.CMDPMOD & 0x40) != 0);//show the actual color of transparent pixels if 1 (they won't be drawn transparent)
	int currentShape = cmd.CMDCTRL & 0x7;
	int isTextured=1;

	if(mesh && (x^y)&1)
		return;

	if(currentShape == 4 || currentShape == 5 || currentShape == 6)
		isTextured = 0;

	if (cmd.CMDPMOD & 0x0400) PushUserClipping((cmd.CMDPMOD >> 9) & 0x1);

	if (x >= vdp1clipxstart &&
		x < vdp1clipxend &&
		y >= vdp1clipystart &&
		y < vdp1clipyend)
	{}
	else
		return;

	if (cmd.CMDPMOD & 0x0400) PopUserClipping();


	if ( SPD || (currentPixel & currentPixelIsVisible))
	{
		switch( cmd.CMDPMOD & 0x7 )//we want bits 0,1,2
		{
		case 0:	// replace
			if (!((currentPixel == 0) && !SPD))
				*(iPix) = currentPixel;
			break;
		case 1: // shadow, TODO
			*(iPix) = currentPixel;
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
				(((cmd.CMDPMOD >> 3) & 0x7) != 5) &&
				(((cmd.CMDPMOD >> 3) & 0x7) != 1) &&
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

        if(*iPix & 0x8000) {
            vdp1draw_info.priosused[vdp1draw_info.prioritytable[0]] = 1;
        }
        else if(*iPix) {
            u16 p = *iPix;
            int s, prio, c;

            Vdp1ProcessSpritePixel(vdp1spritetype, &p, &s, &prio, &c);
            vdp1draw_info.priosused[prio] = 1;
        }
	}
}