#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
typedef  int u32 ;
struct TYPE_5__ {scalar_t__ T0; } ;
struct TYPE_6__ {TYPE_1__ part; } ;
struct TYPE_7__ {size_t* CT; int RA0; TYPE_2__ ProgControlPort; void*** MD; } ;
typedef  TYPE_3__ scudspregs_struct ;

/* Variables and functions */
 void* MappedMemoryReadLong (int) ; 

void dsp_dma01(scudspregs_struct *sc, u32 inst)
{
    u32 imm = ((inst & 0xFF));
    u8  sel = ((inst >> 8) & 0x03);
    u8  add;
    u8  addr = sc->CT[sel];
    u32 i;

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

    if (add != 1)
    {
        for (i = 0; i < imm; i++)
        {
            sc->MD[sel][sc->CT[sel]] = MappedMemoryReadLong((sc->RA0 << 2));
            sc->CT[sel]++;
            sc->CT[sel] &= 0x3F;
            sc->RA0 += 1; // add?
        }
    }
    else{
        for (i = 0; i < imm; i++)
        {
            sc->MD[sel][sc->CT[sel]] = MappedMemoryReadLong((sc->RA0 << 2));
            sc->CT[sel]++;
            sc->CT[sel] &= 0x3F;
            sc->RA0 += 1;
        }
    }

    sc->ProgControlPort.part.T0 = 0;
}