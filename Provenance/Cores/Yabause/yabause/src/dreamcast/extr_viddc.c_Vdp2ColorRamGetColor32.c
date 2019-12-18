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
typedef  int u32 ;
struct TYPE_2__ {int ColorMode; } ;

/* Variables and functions */
 int SAT2YAB2_32 (int,int,int) ; 
 int SAT2YAB32 (int,int) ; 
 int T2ReadWord (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Vdp2ColorRam ; 
 TYPE_1__ Vdp2Internal ; 

__attribute__((used)) static u32 Vdp2ColorRamGetColor32(u32 colorindex, int alpha)    {
    switch(Vdp2Internal.ColorMode)  {
        case 0:
        case 1:
        {
            u32 tmp;
            colorindex <<= 1;
            tmp = T2ReadWord(Vdp2ColorRam, colorindex & 0xFFF);
            return SAT2YAB32(alpha, tmp);
        }
        case 2:
        {
            u32 tmp1, tmp2;
            colorindex <<= 2;
            colorindex &= 0xFFF;
            tmp1 = T2ReadWord(Vdp2ColorRam, colorindex);
            tmp2 = T2ReadWord(Vdp2ColorRam, colorindex+2);
            return SAT2YAB2_32(alpha, tmp1, tmp2);
        }
        default:
            break;
    }

    return 0;
}