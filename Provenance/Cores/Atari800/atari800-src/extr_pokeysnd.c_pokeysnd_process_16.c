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
typedef  int UWORD ;
typedef  scalar_t__ UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  pokeysnd_process_8 (int*,int) ; 

__attribute__((used)) static void pokeysnd_process_16(void *sndbuffer, int sndn)
{
	UWORD *buffer = (UWORD *) sndbuffer;
	int i;

	pokeysnd_process_8(buffer, sndn);

	for (i = sndn - 1; i >= 0; i--) {
		int smp = ((int) (((UBYTE *) buffer)[i]) - 0x80) * 0x100;

		if (smp > 32767)
			smp = 32767;
		else if (smp < -32768)
			smp = -32768;

		buffer[i] = smp;
	}
}