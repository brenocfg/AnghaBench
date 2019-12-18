#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int* POKEY_AUDCTL ; 
 int* POKEY_AUDF ; 
 size_t POKEY_CHAN3 ; 
 size_t POKEY_CHAN4 ; 
 int POKEY_SKCTL ; 

__attribute__((used)) static int POKEY_siocheck(void)
{
	return (((POKEY_AUDF[POKEY_CHAN3] == 0x28 || POKEY_AUDF[POKEY_CHAN3] == 0x10
	        || POKEY_AUDF[POKEY_CHAN3] == 0x08 || POKEY_AUDF[POKEY_CHAN3] == 0x0a)
		&& POKEY_AUDF[POKEY_CHAN4] == 0x00) /* intelligent peripherals speeds */
		|| (POKEY_SKCTL & 0x78) == 0x28) /* cassette save mode */
		&& (POKEY_AUDCTL[0] & 0x28) == 0x28;
}