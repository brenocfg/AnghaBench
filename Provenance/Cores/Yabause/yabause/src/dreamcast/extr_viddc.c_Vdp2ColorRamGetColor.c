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
typedef  int uint16 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int ColorMode; } ;

/* Variables and functions */
 int SAT2YAB1 (int /*<<< orphan*/ ) ; 
 int SAT2YAB2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  T2ReadWord (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Vdp2ColorRam ; 
 TYPE_1__ Vdp2Internal ; 

__attribute__((used)) static uint16 Vdp2ColorRamGetColor(u32 colorindex)   {
    u16 tmp;

    switch(Vdp2Internal.ColorMode)  {
        case 0:
        case 1:
        {
            colorindex <<= 1;
            tmp = T2ReadWord(Vdp2ColorRam, colorindex & 0xFFF);
            return SAT2YAB1(tmp) | 0x8000;
        }
        case 2:
        {
            u16 tmp2;
            colorindex <<= 2;
            colorindex &= 0xFFF;
            tmp = T2ReadWord(Vdp2ColorRam, colorindex);
            tmp2 = T2ReadWord(Vdp2ColorRam, colorindex+2);
            return SAT2YAB2(tmp, tmp2) | 0x8000;
        }
        default:
            break;
    }

    return 0;
}