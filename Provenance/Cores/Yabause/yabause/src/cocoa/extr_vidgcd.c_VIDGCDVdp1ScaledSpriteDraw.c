#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  Vdp1 ;
struct TYPE_5__ {int localX; int localY; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {int CMDXA; int CMDYA; int CMDCTRL; int CMDSIZE; scalar_t__ CMDYB; scalar_t__ CMDXB; scalar_t__ CMDYC; scalar_t__ CMDXC; } ;

/* Variables and functions */
 int /*<<< orphan*/  Vdp1Ram ; 
 int /*<<< orphan*/  Vdp1ReadCommand (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* Vdp1Regs ; 
 TYPE_1__ cmd ; 
 int /*<<< orphan*/  drawQuad (int,int,int,int,int,int,int,int) ; 

void VIDGCDVdp1ScaledSpriteDraw(u8 * ram, Vdp1 * regs, u8* back_framebuffer){

	s32 topLeftx,topLefty,topRightx,topRighty,bottomRightx,bottomRighty,bottomLeftx,bottomLefty;
	int spriteWidth;
	int spriteHeight;
	int x0,y0,x1,y1;
	Vdp1ReadCommand(&cmd, Vdp1Regs->addr, Vdp1Ram);

	x0 = cmd.CMDXA + Vdp1Regs->localX;
	y0 = cmd.CMDYA + Vdp1Regs->localY;

	switch ((cmd.CMDCTRL >> 8) & 0xF)
	{
	case 0x0: // Only two coordinates
	default:
		x1 = ((int)cmd.CMDXC) - x0 + Vdp1Regs->localX + 1;
		y1 = ((int)cmd.CMDYC) - y0 + Vdp1Regs->localY + 1;
		break;
	case 0x5: // Upper-left
		x1 = ((int)cmd.CMDXB) + 1;
		y1 = ((int)cmd.CMDYB) + 1;
		break;
	case 0x6: // Upper-Center
		x1 = ((int)cmd.CMDXB);
		y1 = ((int)cmd.CMDYB);
		x0 = x0 - x1/2;
		x1++;
		y1++;
		break;
	case 0x7: // Upper-Right
		x1 = ((int)cmd.CMDXB);
		y1 = ((int)cmd.CMDYB);
		x0 = x0 - x1;
		x1++;
		y1++;
		break;
	case 0x9: // Center-left
		x1 = ((int)cmd.CMDXB);
		y1 = ((int)cmd.CMDYB);
		y0 = y0 - y1/2;
		x1++;
		y1++;
		break;
	case 0xA: // Center-center
		x1 = ((int)cmd.CMDXB);
		y1 = ((int)cmd.CMDYB);
		x0 = x0 - x1/2;
		y0 = y0 - y1/2;
		x1++;
		y1++;
		break;
	case 0xB: // Center-right
		x1 = ((int)cmd.CMDXB);
		y1 = ((int)cmd.CMDYB);
		x0 = x0 - x1;
		y0 = y0 - y1/2;
		x1++;
		y1++;
		break;
	case 0xD: // Lower-left
		x1 = ((int)cmd.CMDXB);
		y1 = ((int)cmd.CMDYB);
		y0 = y0 - y1;
		x1++;
		y1++;
		break;
	case 0xE: // Lower-center
		x1 = ((int)cmd.CMDXB);
		y1 = ((int)cmd.CMDYB);
		x0 = x0 - x1/2;
		y0 = y0 - y1;
		x1++;
		y1++;
		break;
	case 0xF: // Lower-right
		x1 = ((int)cmd.CMDXB);
		y1 = ((int)cmd.CMDYB);
		x0 = x0 - x1;
		y0 = y0 - y1;
		x1++;
		y1++;
		break;
	}

	spriteWidth = ((cmd.CMDSIZE >> 8) & 0x3F) * 8;
	spriteHeight = cmd.CMDSIZE & 0xFF;

	topLeftx = x0;
	topLefty = y0;

	topRightx = x1 + x0 - 1;
	topRighty = topLefty;

	bottomRightx = x1 + x0 - 1;
	bottomRighty = y1 + y0 - 1;

	bottomLeftx = topLeftx;
	bottomLefty = y1 + y0 - 1;

	drawQuad(topLeftx,topLefty,bottomLeftx,bottomLefty,topRightx,topRighty,bottomRightx,bottomRighty);
}