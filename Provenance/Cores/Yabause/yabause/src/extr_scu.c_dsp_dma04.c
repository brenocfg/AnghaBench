#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_6__ {scalar_t__ T0; } ;
struct TYPE_7__ {TYPE_1__ part; } ;
struct TYPE_8__ {int** MD; size_t* CT; int WA0; TYPE_2__ ProgControlPort; } ;
typedef  TYPE_3__ scudspregs_struct ;
struct TYPE_9__ {int /*<<< orphan*/ * CT; } ;

/* Variables and functions */
 int /*<<< orphan*/  MappedMemoryWriteLong (int,int) ; 
 TYPE_5__* ScuDsp ; 

void dsp_dma04(scudspregs_struct *sc, u32 inst)
{
    u32 Counter = 0;
    u32 add = 0;
    u32 sel = ((inst >> 8) & 0x03);
    u32 i;

    switch ((inst & 0x7))
    {
    case 0x00: Counter = sc->MD[0][sc->CT[0]]; break;
    case 0x01: Counter = sc->MD[1][sc->CT[1]]; break;
    case 0x02: Counter = sc->MD[2][sc->CT[2]]; break;
    case 0x03: Counter = sc->MD[3][sc->CT[3]]; break;
    case 0x04: Counter = sc->MD[0][sc->CT[0]]; ScuDsp->CT[0]++; break;
    case 0x05: Counter = sc->MD[1][sc->CT[1]]; ScuDsp->CT[1]++; break;
    case 0x06: Counter = sc->MD[2][sc->CT[2]]; ScuDsp->CT[2]++; break;
    case 0x07: Counter = sc->MD[3][sc->CT[3]]; ScuDsp->CT[3]++; break;
    }
    
    switch (((inst >> 15) & 0x07))
    {
    case 0: add = 0; break;
    case 1: add = 1; break;
    case 2: add = 2; break;
    case 3: add = 4; break;
    case 4: add = 8; break;
    case 5: add = 16; break;
    case 6: add = 32; break;
    case 7: add = 64; break;
    }

    for (i = 0; i < Counter; i++)
    {
        u32 Val = sc->MD[sel][sc->CT[sel]];
        u32 Adr = (sc->WA0 << 2);
        MappedMemoryWriteLong(Adr, Val);
        sc->CT[sel]++;
        sc->CT[sel] &= 0x3F;
        sc->WA0 += 1;

    }
    sc->ProgControlPort.part.T0 = 0;
}