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
struct TYPE_4__ {int CMDCOLR; } ;
typedef  TYPE_1__ vdp1cmd_struct ;
typedef  int u8 ;
struct TYPE_5__ {int SPCTL; int PRISA; } ;

/* Variables and functions */
 int /*<<< orphan*/  VDP1LOG (char*,int) ; 
 TYPE_2__* Vdp2Regs ; 

__attribute__((used)) static u8 Vdp1ReadPriority(vdp1cmd_struct *cmd) {
    u8 SPCLMD = Vdp2Regs->SPCTL;
    u8 sprite_register;
    u8 *sprprilist = (u8 *)&Vdp2Regs->PRISA;

    if ((SPCLMD & 0x20) && (cmd->CMDCOLR & 0x8000)) {
        // RGB data, use register 0
        return Vdp2Regs->PRISA & 0x07;
    }
    else    {
        u8 sprite_type = SPCLMD & 0x0F;
        switch(sprite_type) {
            case 0:
                sprite_register = ((cmd->CMDCOLR & 0x8000) |
                                   (~cmd->CMDCOLR & 0x4000)) >> 14;
                return sprprilist[sprite_register ^ 1] & 0x07;
                break;
            case 1:
                sprite_register = ((cmd->CMDCOLR & 0xC000) |
                                   (~cmd->CMDCOLR & 0x2000)) >> 13;
                return sprprilist[sprite_register ^ 1] & 0x07;
                break;
            case 3:
                sprite_register = ((cmd->CMDCOLR & 0x4000) |
                                   (~cmd->CMDCOLR & 0x2000)) >> 13;
                return sprprilist[sprite_register ^ 1] & 0x07;
                break;
            case 4:
                sprite_register = ((cmd->CMDCOLR & 0x4000) |
                                   (~cmd->CMDCOLR & 0x2000)) >> 13;
                return sprprilist[sprite_register ^ 1] & 0x07;
                break;
            case 5:
                sprite_register = ((cmd->CMDCOLR & 0x6000) |
                                   (~cmd->CMDCOLR & 0x1000)) >> 12;
                return sprprilist[sprite_register ^ 1] & 0x07;
                break;
            case 6:
                sprite_register = ((cmd->CMDCOLR & 0x6000) |
                                   (~cmd->CMDCOLR & 0x1000)) >> 12;
                return sprprilist[sprite_register ^ 1] & 0x07;
                break;
            case 7:
                sprite_register = ((cmd->CMDCOLR & 0x6000) |
                                   (~cmd->CMDCOLR & 0x1000)) >> 12;
                return sprprilist[sprite_register ^ 1] & 0x07;
                break;
            default:
                VDP1LOG("sprite type %d not implemented\n", sprite_type);
                return 0x07;
                break;
        }
    }
}