#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int CMDSIZE; int CMDPMOD; int CMDCTRL; scalar_t__ CMDYD; scalar_t__ CMDXD; scalar_t__ CMDYC; scalar_t__ CMDXC; scalar_t__ CMDYB; scalar_t__ CMDXB; scalar_t__ CMDYA; scalar_t__ CMDXA; } ;
typedef  TYPE_1__ vdp1cmd_struct ;
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  sprite ;
struct TYPE_13__ {float az; float bz; float cz; void* cuv; void* buv; void* auv; scalar_t__ dy; scalar_t__ dx; scalar_t__ cy; scalar_t__ cx; scalar_t__ by; scalar_t__ bx; scalar_t__ ay; scalar_t__ ax; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ pvr_sprite_txr_t ;
typedef  int /*<<< orphan*/  pvr_sprite_hdr_t ;
typedef  int /*<<< orphan*/  pvr_list_t ;
struct TYPE_15__ {scalar_t__ localY; scalar_t__ localX; int /*<<< orphan*/  addr; } ;
struct TYPE_14__ {int w; int h; float uf; float vf; } ;

/* Variables and functions */
 int /*<<< orphan*/  PVR_CMD_VERTEX_EOL ; 
 int /*<<< orphan*/  PVR_LIST_PT_POLY ; 
 int /*<<< orphan*/  PVR_LIST_TR_POLY ; 
 void* PVR_PACK_16BIT_UV (float,float) ; 
 int /*<<< orphan*/  Vdp1ReadCommand (TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t Vdp1ReadPriority (TYPE_1__*) ; 
 int Vdp1ReadTexture (TYPE_1__*,TYPE_2__*) ; 
 TYPE_7__* Vdp1Regs ; 
 TYPE_6__ cur_spr ; 
 float* priority_levels ; 
 TYPE_2__ pt_sprite_hdr ; 
 int /*<<< orphan*/  pvr_list_prim (int /*<<< orphan*/ ,TYPE_2__*,int) ; 
 TYPE_2__ tr_sprite_hdr ; 

__attribute__((used)) static void VIDDCVdp1DistortedSpriteDraw(void)  {
    vdp1cmd_struct cmd;
    u8 z;
    pvr_sprite_txr_t sprite;
    pvr_list_t list;
    int num;

    Vdp1ReadCommand(&cmd, Vdp1Regs->addr);

    cur_spr.w = ((cmd.CMDSIZE >> 8) & 0x3F) * 8;
    cur_spr.h = cmd.CMDSIZE & 0xFF;

    if((cmd.CMDPMOD & 0x7) == 0x3) {
        list = PVR_LIST_TR_POLY;
        num = Vdp1ReadTexture(&cmd, &tr_sprite_hdr);

        if(num == 0)
            return;
        else
            pvr_list_prim(PVR_LIST_TR_POLY, &tr_sprite_hdr,
                          sizeof(pvr_sprite_hdr_t));
    }
    else    {
        num = Vdp1ReadTexture(&cmd, &pt_sprite_hdr);
        list = PVR_LIST_PT_POLY;

        if(num == 0)
            return;
        else
            pvr_list_prim(PVR_LIST_PT_POLY, &pt_sprite_hdr,
                          sizeof(pvr_sprite_hdr_t));
    }

    z = Vdp1ReadPriority(&cmd);

    sprite.flags = PVR_CMD_VERTEX_EOL;
    sprite.ax = cmd.CMDXA + Vdp1Regs->localX;
    sprite.ay = cmd.CMDYA + Vdp1Regs->localY;
    sprite.az = priority_levels[z];

    sprite.bx = cmd.CMDXB + Vdp1Regs->localX + 1;
    sprite.by = cmd.CMDYB + Vdp1Regs->localY;
    sprite.bz = priority_levels[z];

    sprite.cx = cmd.CMDXC + Vdp1Regs->localX + 1;
    sprite.cy = cmd.CMDYC + Vdp1Regs->localY + 1;
    sprite.cz = priority_levels[z];

    sprite.dx = cmd.CMDXD + Vdp1Regs->localX;
    sprite.dy = cmd.CMDYD + Vdp1Regs->localY + 1;

    sprite.auv = PVR_PACK_16BIT_UV(((cmd.CMDCTRL & 0x0010) ? cur_spr.uf : 0.0f),
                                  ((cmd.CMDCTRL & 0x0020) ? cur_spr.vf : 0.0f));
    sprite.buv = PVR_PACK_16BIT_UV(((cmd.CMDCTRL & 0x0010) ? 0.0f : cur_spr.uf),
                                  ((cmd.CMDCTRL & 0x0020) ? cur_spr.vf : 0.0f));
    sprite.cuv = PVR_PACK_16BIT_UV(((cmd.CMDCTRL & 0x0010) ? 0.0f : cur_spr.uf),
                                  ((cmd.CMDCTRL & 0x0020) ? 0.0f : cur_spr.vf));
    pvr_list_prim(list, &sprite, sizeof(sprite));

    priority_levels[z] += 0.000001f;
}