#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_3__ {int /*<<< orphan*/  (* Write_Word ) (int,int) ;} ;
typedef  TYPE_1__ c68k_struc ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int,int) ; 
 int /*<<< orphan*/  stub2 (int,int) ; 
 int /*<<< orphan*/  stub3 (int,int) ; 
 int /*<<< orphan*/  stub4 (int,int) ; 

void C68k_Write_Long(c68k_struc *cpu, u32 adr, u32 data)
{
#ifdef C68K_BIG_ENDIAN
    cpu->Write_Word(adr, data >> 16);
    cpu->Write_Word(adr + 2, data & 0xFFFF);
#else
    cpu->Write_Word(adr, data >> 16);
    cpu->Write_Word(adr + 2, data & 0xFFFF);
#endif
}