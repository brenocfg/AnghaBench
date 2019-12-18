#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int W; } ;
struct TYPE_6__ {TYPE_1__ SP; scalar_t__ BasePC; scalar_t__ PC; } ;
struct TYPE_5__ {unsigned int Z80PC; unsigned int Z80PC_BASE; int Z80SP; int Z80SP_BASE; } ;

/* Variables and functions */
 TYPE_3__ CZ80 ; 
 TYPE_2__ drZ80 ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned int,int) ; 

void z80_debug(char *dstr)
{
#if defined(_USE_DRZ80)
  sprintf(dstr, "Z80 state: PC: %04x SP: %04x\n", drZ80.Z80PC-drZ80.Z80PC_BASE, drZ80.Z80SP-drZ80.Z80SP_BASE);
#elif defined(_USE_CZ80)
  sprintf(dstr, "Z80 state: PC: %04x SP: %04x\n", (unsigned int)(CZ80.PC - CZ80.BasePC), CZ80.SP.W);
#endif
}