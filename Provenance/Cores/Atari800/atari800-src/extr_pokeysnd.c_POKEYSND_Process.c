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
 int /*<<< orphan*/  POKEYSND_Process_ptr (void*,int) ; 
 int /*<<< orphan*/  SndSave_WriteToSoundFile (unsigned char const*,int) ; 
 int /*<<< orphan*/  VOTRAXSND_Process (void*,int) ; 

void POKEYSND_Process(void *sndbuffer, int sndn)
{
	POKEYSND_Process_ptr(sndbuffer, sndn);
#if defined(PBI_XLD) || defined (VOICEBOX)
	VOTRAXSND_Process(sndbuffer,sndn);
#endif
#if !defined(__PLUS) && !defined(ASAP)
	SndSave_WriteToSoundFile((const unsigned char *)sndbuffer, sndn);
#endif
}