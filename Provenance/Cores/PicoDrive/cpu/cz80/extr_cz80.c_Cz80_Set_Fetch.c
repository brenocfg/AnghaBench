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
struct TYPE_3__ {int* Fetch; scalar_t__* OPFetch; } ;
typedef  TYPE_1__ cz80_struc ;
typedef  int UINT32 ;
typedef  int FPTR ;

/* Variables and functions */
 int CZ80_FETCH_SFT ; 

void Cz80_Set_Fetch(cz80_struc *CPU, UINT32 low_adr, UINT32 high_adr, FPTR fetch_adr)
{
	int i, j;

	i = low_adr >> CZ80_FETCH_SFT;
	j = high_adr >> CZ80_FETCH_SFT;
	fetch_adr -= i << CZ80_FETCH_SFT;

	while (i <= j)
	{
		CPU->Fetch[i] = fetch_adr;
#if CZ80_ENCRYPTED_ROM
		CPU->OPFetch[i] = 0;
#endif
		i++;
	}
}