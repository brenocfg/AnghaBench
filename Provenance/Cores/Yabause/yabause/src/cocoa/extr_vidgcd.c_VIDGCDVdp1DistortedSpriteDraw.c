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
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  Vdp1 ;
struct TYPE_5__ {scalar_t__ localY; scalar_t__ localX; int /*<<< orphan*/  addr; } ;
struct TYPE_4__ {scalar_t__ CMDYD; scalar_t__ CMDXD; scalar_t__ CMDYC; scalar_t__ CMDXC; scalar_t__ CMDYB; scalar_t__ CMDXB; scalar_t__ CMDYA; scalar_t__ CMDXA; } ;

/* Variables and functions */
 int /*<<< orphan*/  Vdp1Ram ; 
 int /*<<< orphan*/  Vdp1ReadCommand (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* Vdp1Regs ; 
 TYPE_1__ cmd ; 
 int /*<<< orphan*/  drawQuad (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void VIDGCDVdp1DistortedSpriteDraw(u8 * ram, Vdp1 * regs, u8* back_framebuffer) {

	s32 xa,ya,xb,yb,xc,yc,xd,yd;

	Vdp1ReadCommand(&cmd, Vdp1Regs->addr, Vdp1Ram);

    xa = (s32)(cmd.CMDXA + Vdp1Regs->localX);
    ya = (s32)(cmd.CMDYA + Vdp1Regs->localY);

    xb = (s32)(cmd.CMDXB + Vdp1Regs->localX);
    yb = (s32)(cmd.CMDYB + Vdp1Regs->localY);

    xc = (s32)(cmd.CMDXC + Vdp1Regs->localX);
    yc = (s32)(cmd.CMDYC + Vdp1Regs->localY);

    xd = (s32)(cmd.CMDXD + Vdp1Regs->localX);
    yd = (s32)(cmd.CMDYD + Vdp1Regs->localY);

	drawQuad(xa,ya,xd,yd,xb,yb,xc,yc);
}