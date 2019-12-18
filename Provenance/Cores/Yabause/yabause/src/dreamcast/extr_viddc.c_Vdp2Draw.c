#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int mode2; int mode3; float az; float bx; float bz; float cx; float cy; float cz; float dy; void* cuv; void* buv; void* auv; scalar_t__ dx; scalar_t__ by; scalar_t__ ay; scalar_t__ ax; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ pvr_sprite_txr_t ;
typedef  int /*<<< orphan*/  pvr_sprite_hdr_t ;

/* Variables and functions */
 int /*<<< orphan*/  PVR_CMD_VERTEX_EOL ; 
 int /*<<< orphan*/  PVR_LIST_PT_POLY ; 
 void* PVR_PACK_16BIT_UV (float,float) ; 
 int PVR_TA_PM2_USIZE_MASK ; 
 int PVR_TA_PM2_USIZE_SHIFT ; 
 int PVR_TA_PM2_VSIZE_MASK ; 
 int PVR_TA_PM2_VSIZE_SHIFT ; 
 int PVR_TXRFMT_NONTWIDDLED ; 
 int cur_vdp2 ; 
 float* priority_levels ; 
 TYPE_1__ pt_sprite_hdr ; 
 int /*<<< orphan*/  pvr_list_prim (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 float vdp2height ; 
 float vdp2width ; 

__attribute__((used)) static void Vdp2Draw(int priority)  {
    pvr_sprite_txr_t sprite;

    pt_sprite_hdr.mode2 &= (~(PVR_TA_PM2_USIZE_MASK | PVR_TA_PM2_VSIZE_MASK));
    pt_sprite_hdr.mode2 |= (6 << PVR_TA_PM2_USIZE_SHIFT) |
                           (5 << PVR_TA_PM2_VSIZE_SHIFT);
    pt_sprite_hdr.mode3 = ((cur_vdp2 & 0x00FFFFF8) >> 3) |
                          (PVR_TXRFMT_NONTWIDDLED);

    pvr_list_prim(PVR_LIST_PT_POLY, &pt_sprite_hdr, sizeof(pvr_sprite_hdr_t));

    sprite.flags = PVR_CMD_VERTEX_EOL;
    sprite.ax = 0;
    sprite.ay = 0;
    sprite.az = priority_levels[priority];

    sprite.bx = vdp2width;
    sprite.by = 0;
    sprite.bz = priority_levels[priority];

    sprite.cx = vdp2width;
    sprite.cy = vdp2height;
    sprite.cz = priority_levels[priority];

    sprite.dx = 0;
    sprite.dy = vdp2height;

    sprite.auv = PVR_PACK_16BIT_UV(0.0f, 0.0f);
    sprite.buv = PVR_PACK_16BIT_UV(vdp2width / 512.0f, 0.0f);
    sprite.cuv = PVR_PACK_16BIT_UV(vdp2width / 512.0f, vdp2height / 256.0f);
    pvr_list_prim(PVR_LIST_PT_POLY, &sprite, sizeof(pvr_sprite_txr_t));

    priority_levels[priority] += 0.000001f;
}