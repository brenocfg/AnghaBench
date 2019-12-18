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
 int POKEYSND_BIT16 ; 
 int POKEYSND_snd_flags ; 
 int /*<<< orphan*/  SndSave_CloseSoundFile () ; 
 int byteswritten ; 
 int fwrite (unsigned char const*,int,unsigned int,scalar_t__) ; 
 scalar_t__ sndoutput ; 

int SndSave_WriteToSoundFile(const unsigned char *ucBuffer, unsigned int uiSize)
{
	/* XXX FIXME: doesn't work with big-endian architectures */
	if (sndoutput && ucBuffer && uiSize) {
		int result;
		if (POKEYSND_snd_flags & POKEYSND_BIT16)
			uiSize <<= 1;
		result = fwrite(ucBuffer, 1, uiSize, sndoutput);
		byteswritten += result;
		if (result != uiSize) {
			SndSave_CloseSoundFile();
		}

		return result;
	}

	return 0;
}