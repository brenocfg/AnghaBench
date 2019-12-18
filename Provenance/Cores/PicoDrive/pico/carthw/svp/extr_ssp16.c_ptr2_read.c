#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned short u32 ;
struct TYPE_4__ {size_t* r0; size_t* r1; int /*<<< orphan*/ * RAM1; int /*<<< orphan*/ * RAM0; } ;
struct TYPE_3__ {scalar_t__ iram_rom; } ;

/* Variables and functions */
 int EL_ANOMALY ; 
 int EL_SVP ; 
 int /*<<< orphan*/  GET_PPC_OFFS () ; 
 int /*<<< orphan*/  elprintf (int,char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* ssp ; 
 TYPE_1__* svp ; 

__attribute__((used)) static u32 ptr2_read(int op)
{
	int mv = 0, t = (op&3) | ((op>>6)&4) | ((op<<1)&0x18);
	switch (t)
	{
		// mod=0 (00)
		case 0x00:
		case 0x01:
		case 0x02: mv = ssp->RAM0[ssp->r0[t&3]]++; break;
		case 0x03: mv = ssp->RAM0[0]++; break;
		case 0x04:
		case 0x05:
		case 0x06: mv = ssp->RAM1[ssp->r1[t&3]]++; break;
		case 0x07: mv = ssp->RAM1[0]++; break;
		// mod=1 (01)
		case 0x0b: mv = ssp->RAM0[1]++; break;
		case 0x0f: mv = ssp->RAM1[1]++; break;
		// mod=2 (10)
		case 0x13: mv = ssp->RAM0[2]++; break;
		case 0x17: mv = ssp->RAM1[2]++; break;
		// mod=3 (11)
		case 0x1b: mv = ssp->RAM0[3]++; break;
		case 0x1f: mv = ssp->RAM1[3]++; break;
		default:   elprintf(EL_SVP|EL_ANOMALY, "ssp FIXME: invalid mod in ((rX))? @ %04x", GET_PPC_OFFS());
		           return 0;
	}

	return ((unsigned short *)svp->iram_rom)[mv];
}