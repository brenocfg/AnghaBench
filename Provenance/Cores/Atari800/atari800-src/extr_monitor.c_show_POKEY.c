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
 scalar_t__ POKEYSND_stereo_enabled ; 
 int* POKEY_AUDC ; 
 int* POKEY_AUDCTL ; 
 int* POKEY_AUDF ; 
 size_t POKEY_CHAN1 ; 
 size_t POKEY_CHAN2 ; 
 size_t POKEY_CHAN3 ; 
 size_t POKEY_CHAN4 ; 
 size_t POKEY_CHIP2 ; 
 int POKEY_IRQEN ; 
 int POKEY_IRQST ; 
 int POKEY_KBCODE ; 
 int POKEY_SKCTL ; 
 int POKEY_SKSTAT ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void show_POKEY(void)
{
	printf("AUDF1= %02X    AUDF2= %02X    AUDF3= %02X    AUDF4= %02X    AUDCTL=%02X    KBCODE=%02X\n",
		   POKEY_AUDF[POKEY_CHAN1], POKEY_AUDF[POKEY_CHAN2], POKEY_AUDF[POKEY_CHAN3], POKEY_AUDF[POKEY_CHAN4], POKEY_AUDCTL[0], POKEY_KBCODE);
	printf("AUDC1= %02X    AUDC2= %02X    AUDC3= %02X    AUDC4= %02X    IRQEN= %02X    IRQST= %02X\n",
		   POKEY_AUDC[POKEY_CHAN1], POKEY_AUDC[POKEY_CHAN2], POKEY_AUDC[POKEY_CHAN3], POKEY_AUDC[POKEY_CHAN4], POKEY_IRQEN, POKEY_IRQST);
	printf("SKSTAT=%02X    SKCTL= %02X\n", POKEY_SKSTAT, POKEY_SKCTL);
#ifdef STEREO_SOUND
	if (POKEYSND_stereo_enabled) {
		printf("Second chip:\n");
		printf("AUDF1= %02X    AUDF2= %02X    AUDF3= %02X    AUDF4= %02X    AUDCTL=%02X\n",
			   POKEY_AUDF[POKEY_CHAN1 + POKEY_CHIP2], POKEY_AUDF[POKEY_CHAN2 + POKEY_CHIP2], POKEY_AUDF[POKEY_CHAN3 + POKEY_CHIP2], POKEY_AUDF[POKEY_CHAN4 + POKEY_CHIP2], POKEY_AUDCTL[1]);
		printf("AUDC1= %02X    AUDC2= %02X    AUDC3= %02X    AUDC4= %02X\n",
			   POKEY_AUDC[POKEY_CHAN1 + POKEY_CHIP2], POKEY_AUDC[POKEY_CHAN2 + POKEY_CHIP2], POKEY_AUDC[POKEY_CHAN3 + POKEY_CHIP2], POKEY_AUDC[POKEY_CHAN4 + POKEY_CHIP2]);
	}
#endif
}