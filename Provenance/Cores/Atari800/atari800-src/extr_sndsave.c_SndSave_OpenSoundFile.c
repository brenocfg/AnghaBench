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
 int FALSE ; 
 int POKEYSND_BIT16 ; 
 int POKEYSND_num_pokeys ; 
 int POKEYSND_playback_freq ; 
 int POKEYSND_snd_flags ; 
 int /*<<< orphan*/  SndSave_CloseSoundFile () ; 
 int TRUE ; 
 scalar_t__ byteswritten ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fputc (int,int /*<<< orphan*/ *) ; 
 int fwrite (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sndoutput ; 
 int /*<<< orphan*/  write32 (int) ; 

int SndSave_OpenSoundFile(const char *szFileName)
{
	SndSave_CloseSoundFile();

	sndoutput = fopen(szFileName, "wb");

	if (sndoutput == NULL)
		return FALSE;
	/*
	The RIFF header:

	  Offset  Length   Contents
	  0       4 bytes  'RIFF'
	  4       4 bytes  <file length - 8>
	  8       4 bytes  'WAVE'

	The fmt chunk:

	  12      4 bytes  'fmt '
	  16      4 bytes  0x00000010     // Length of the fmt data (16 bytes)
	  20      2 bytes  0x0001         // Format tag: 1 = PCM
	  22      2 bytes  <channels>     // Channels: 1 = mono, 2 = stereo
	  24      4 bytes  <sample rate>  // Samples per second: e.g., 44100
	  28      4 bytes  <bytes/second> // sample rate * block align
	  32      2 bytes  <block align>  // channels * bits/sample / 8
	  34      2 bytes  <bits/sample>  // 8 or 16

	The data chunk:

	  36      4 bytes  'data'
	  40      4 bytes  <length of the data block>
	  44        bytes  <sample data>

	All chunks must be word-aligned.

	Good description of WAVE format: http://www.sonicspot.com/guide/wavefiles.html
	*/

	if (fwrite("RIFF\0\0\0\0WAVEfmt \x10\0\0\0\1\0", 1, 22, sndoutput) != 22) {
		fclose(sndoutput);
		sndoutput = NULL;
		return FALSE;
	}

	fputc(POKEYSND_num_pokeys, sndoutput);
	fputc(0, sndoutput);
	write32(POKEYSND_playback_freq);


	write32(POKEYSND_playback_freq * (POKEYSND_snd_flags & POKEYSND_BIT16 ? POKEYSND_num_pokeys << 1 : POKEYSND_num_pokeys));

	fputc(POKEYSND_snd_flags & POKEYSND_BIT16 ? POKEYSND_num_pokeys << 1 : POKEYSND_num_pokeys, sndoutput);
	fputc(0, sndoutput);

	fputc(POKEYSND_snd_flags & POKEYSND_BIT16? 16: 8, sndoutput);

	if (fwrite("\0data\0\0\0\0", 1, 9, sndoutput) != 9) {
		fclose(sndoutput);
		sndoutput = NULL;
		return FALSE;
	}

	byteswritten = 0;
	return TRUE;
}