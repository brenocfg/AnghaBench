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
typedef  int u8 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_2__ {int CMDCTRL; int CMDSRCA; int CMDCOLR; int CMDPMOD; } ;

/* Variables and functions */
 int T1ReadWord (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Vdp1Ram ; 
 int Vdp1ReadPattern128 (int,int) ; 
 int Vdp1ReadPattern16 (int,int) ; 
 int Vdp1ReadPattern256 (int,int) ; 
 int Vdp1ReadPattern64 (int,int) ; 
 int Vdp1ReadPattern64k (int,int) ; 
 int /*<<< orphan*/  characterHeight ; 
 int characterWidth ; 
 TYPE_1__ cmd ; 
 int currentPixel ; 
 int currentPixelIsVisible ; 

__attribute__((used)) static int getpixel(int linenumber, int currentlineindex) {

	u32 characterAddress;
	u32 colorlut;
	u16 colorbank;
	u8 SPD;
	int endcode;
	int endcodesEnabled;
	int untexturedColor = 0;
	int isTextured = 1;
	int currentShape = cmd.CMDCTRL & 0x7;
	int flip;

	characterAddress = cmd.CMDSRCA << 3;
	colorbank = cmd.CMDCOLR;
	colorlut = (u32)colorbank << 3;
	SPD = ((cmd.CMDPMOD & 0x40) != 0);//show the actual color of transparent pixels if 1 (they won't be drawn transparent)
	endcodesEnabled = (( cmd.CMDPMOD & 0x80) == 0 )?1:0;
	flip = (cmd.CMDCTRL & 0x30) >> 4;

	//4 polygon, 5 polyline or 6 line
	if(currentShape == 4 || currentShape == 5 || currentShape == 6) {
		isTextured = 0;
		untexturedColor = cmd.CMDCOLR;
	}

	switch( flip ) {
		case 1:
			// Horizontal flipping
			currentlineindex = characterWidth - currentlineindex-1;
			break;
		case 2:
			// Vertical flipping
			linenumber = characterHeight - linenumber-1;

			break;
		case 3:
			// Horizontal/Vertical flipping
			linenumber = characterHeight - linenumber-1;
			currentlineindex = characterWidth - currentlineindex-1;
			break;
	}

	switch ((cmd.CMDPMOD >> 3) & 0x7)
	{
		case 0x0: //4bpp bank
			endcode = 0xf;
			currentPixel = Vdp1ReadPattern16( characterAddress + (linenumber*(characterWidth>>1)), currentlineindex );
			if(isTextured && endcodesEnabled && currentPixel == endcode)
				return 1;
			if (!((currentPixel == 0) && !SPD))
				currentPixel = colorbank | currentPixel;
			currentPixelIsVisible = 0xf;
			break;

		case 0x1://4bpp lut
			endcode = 0xf;
			currentPixel = Vdp1ReadPattern16( characterAddress + (linenumber*(characterWidth>>1)), currentlineindex );
			if(isTextured && endcodesEnabled && currentPixel == endcode)
				return 1;
			if (!(currentPixel == 0 && !SPD))
				currentPixel = T1ReadWord(Vdp1Ram, (currentPixel * 2 + colorlut) & 0x7FFFF);
			currentPixelIsVisible = 0xffff;
			break;
		case 0x2://8pp bank (64 color)
			//is there a hardware bug with endcodes in this color mode?
			//there are white lines around some characters in scud
			//using an endcode of 63 eliminates the white lines
			//but also causes some dropout due to endcodes being triggered that aren't triggered on hardware
			//the closest thing i can do to match the hardware is make all pixels with color index 63 transparent
			//this needs more hardware testing

			endcode = 63;
			currentPixel = Vdp1ReadPattern64( characterAddress + (linenumber*(characterWidth)), currentlineindex );
			if(isTextured && endcodesEnabled && currentPixel == endcode)
				currentPixel = 0;
		//		return 1;
			if (!((currentPixel == 0) && !SPD))
				currentPixel = colorbank | currentPixel;
			currentPixelIsVisible = 0x3f;
			break;
		case 0x3://128 color
			endcode = 0xff;
			currentPixel = Vdp1ReadPattern128( characterAddress + (linenumber*characterWidth), currentlineindex );
			if(isTextured && endcodesEnabled && currentPixel == endcode)
				return 1;
			if (!((currentPixel == 0) && !SPD))
				currentPixel = colorbank | currentPixel;
			currentPixelIsVisible = 0x7f;
			break;
		case 0x4://256 color
			endcode = 0xff;
			currentPixel = Vdp1ReadPattern256( characterAddress + (linenumber*characterWidth), currentlineindex );
			if(isTextured && endcodesEnabled && currentPixel == endcode)
				return 1;
			currentPixelIsVisible = 0xff;
			if (!((currentPixel == 0) && !SPD))
				currentPixel = colorbank | currentPixel;
			break;
		case 0x5://16bpp bank
			endcode = 0x7fff;
			currentPixel = Vdp1ReadPattern64k( characterAddress + (linenumber*characterWidth*2), currentlineindex );
			if(isTextured && endcodesEnabled && currentPixel == endcode)
				return 1;
			currentPixelIsVisible = 0xffff;
			break;
	}

	if(!isTextured)
		currentPixel = untexturedColor;

	//force the MSB to be on if MSBON is set
	currentPixel |= cmd.CMDPMOD & (1 << 15);

	return 0;
}