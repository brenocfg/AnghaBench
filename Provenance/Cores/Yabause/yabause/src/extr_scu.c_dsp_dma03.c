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
struct TYPE_8__ {int** MD; size_t* CT; int RA0; TYPE_2__ ProgControlPort; void** ProgramRam; } ;
typedef  TYPE_3__ scudspregs_struct ;
struct TYPE_9__ {int /*<<< orphan*/ * CT; } ;

/* Variables and functions */
 void* MappedMemoryReadLong (int) ; 
 TYPE_5__* ScuDsp ; 

void dsp_dma03(scudspregs_struct *sc, u32 inst)
{
    u32 Counter = 0;
    u32 i;
    int DestinationId;

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

    DestinationId = (inst >> 8) & 0x7;

    if (DestinationId > 3)
    {
        int incl = 1; //((sc->inst >> 15) & 0x01);
        for (i = 0; i < Counter; i++)
        {
            u32 Adr = (sc->RA0 << 2);
            sc->ProgramRam[i] = MappedMemoryReadLong(Adr);
            sc->RA0 += incl;
        }
    }
    else{

        int incl = 1; //((sc->inst >> 15) & 0x01);
        for (i = 0; i < Counter; i++)
        {
            u32 Adr = (sc->RA0 << 2);

            sc->MD[DestinationId][sc->CT[DestinationId]] = MappedMemoryReadLong(Adr);
            sc->CT[DestinationId]++;
            sc->CT[DestinationId] &= 0x3F;
            sc->RA0 += incl;
        }
    }
    sc->ProgControlPort.part.T0 = 0;
}