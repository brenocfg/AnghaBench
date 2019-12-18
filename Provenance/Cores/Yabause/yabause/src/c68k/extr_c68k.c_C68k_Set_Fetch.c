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
typedef  int pointer ;
struct TYPE_3__ {int* Fetch; } ;
typedef  TYPE_1__ c68k_struc ;

/* Variables and functions */
 int C68K_FETCH_MASK ; 
 int C68K_FETCH_SFT ; 

void C68k_Set_Fetch(c68k_struc *cpu, u32 low_adr, u32 high_adr, pointer fetch_adr)
{
    u32 i, j;

    i = (low_adr >> C68K_FETCH_SFT) & C68K_FETCH_MASK;
    j = (high_adr >> C68K_FETCH_SFT) & C68K_FETCH_MASK;
    fetch_adr -= i << C68K_FETCH_SFT;
    while (i <= j) cpu->Fetch[i++] = fetch_adr;
}