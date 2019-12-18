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
typedef  size_t u32 ;
struct TYPE_3__ {scalar_t__ BasePC; scalar_t__ PC; scalar_t__* Fetch; } ;
typedef  TYPE_1__ c68k_struc ;

/* Variables and functions */
 size_t C68K_FETCH_MASK ; 
 size_t C68K_FETCH_SFT ; 

void C68k_Set_PC(c68k_struc *cpu, u32 val)
{
    cpu->BasePC = cpu->Fetch[(val >> C68K_FETCH_SFT) & C68K_FETCH_MASK];
    cpu->PC = val + cpu->BasePC;
}