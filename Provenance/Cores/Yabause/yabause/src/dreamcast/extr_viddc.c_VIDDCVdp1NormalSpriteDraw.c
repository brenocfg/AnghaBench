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
struct TYPE_12__ {int CMDXA; int CMDYA; int CMDSIZE; int CMDPMOD; int CMDCTRL; } ;
typedef  TYPE_1__ vdp1cmd_struct ;
typedef  size_t u8 ;
typedef  int /*<<< orphan*/  sprite ;
struct TYPE_13__ {int ax; int ay; float az; int bx; int by; float bz; int cx; int cy; float cz; int dx; int dy; void* cuv; void* buv; void* auv; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ pvr_sprite_txr_t ;
typedef  int /*<<< orphan*/  pvr_sprite_hdr_t ;
typedef  int /*<<< orphan*/  pvr_list_t ;
struct TYPE_15__ {int localX; int localY; int /*<<< orphan*/  addr; } ;
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

__attribute__((used)) static void VIDDCVdp1NormalSpriteDraw(void) {
    int x, y, num;
    u8 z;
    vdp1cmd_struct cmd;
    pvr_sprite_txr_t sprite;
    pvr_list_t list;

    Vdp1ReadCommand(&cmd, Vdp1Regs->addr);

    x = Vdp1Regs->localX + cmd.CMDXA;
    y = Vdp1Regs->localY + cmd.CMDYA;
    cur_spr.w = ((cmd.CMDSIZE >> 8) & 0x3F) << 3;
    cur_spr.h = cmd.CMDSIZE & 0xFF;

    if ((cmd.CMDPMOD & 0x07) == 0x03) {
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
    sprite.ax = x;
    sprite.ay = y;
    sprite.az = priority_levels[z];

    sprite.bx = x + cur_spr.w;
    sprite.by = y;
    sprite.bz = priority_levels[z];

    sprite.cx = x + cur_spr.w;
    sprite.cy = y + cur_spr.h;
    sprite.cz = priority_levels[z];

    sprite.dx = x;
    sprite.dy = y + cur_spr.h;

    sprite.auv = PVR_PACK_16BIT_UV(((cmd.CMDCTRL & 0x0010) ? cur_spr.uf : 0.0f),
                                  ((cmd.CMDCTRL & 0x0020) ? cur_spr.vf : 0.0f));
    sprite.buv = PVR_PACK_16BIT_UV(((cmd.CMDCTRL & 0x0010) ? 0.0f : cur_spr.uf),
                                  ((cmd.CMDCTRL & 0x0020) ? cur_spr.vf : 0.0f));
    sprite.cuv = PVR_PACK_16BIT_UV(((cmd.CMDCTRL & 0x0010) ? 0.0f : cur_spr.uf),
                                  ((cmd.CMDCTRL & 0x0020) ? 0.0f : cur_spr.vf));
    pvr_list_prim(list, &sprite, sizeof(sprite));

    priority_levels[z] += 0.000001f;
}