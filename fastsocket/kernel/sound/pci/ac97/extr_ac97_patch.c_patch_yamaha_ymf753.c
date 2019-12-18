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
struct snd_ac97 {int caps; int /*<<< orphan*/ * build_ops; } ;

/* Variables and functions */
 int AC97_BC_BASS_TREBLE ; 
 int /*<<< orphan*/  patch_yamaha_ymf753_ops ; 

__attribute__((used)) static int patch_yamaha_ymf753(struct snd_ac97 * ac97)
{
	/* Patch for Yamaha YMF753, Copyright (c) by David Shust, dshust@shustring.com.
	   This chip has nonstandard and extended behaviour with regard to its S/PDIF output.
	   The AC'97 spec states that the S/PDIF signal is to be output at pin 48.
	   The YMF753 will ouput the S/PDIF signal to pin 43, 47 (EAPD), or 48.
	   By default, no output pin is selected, and the S/PDIF signal is not output.
	   There is also a bit to mute S/PDIF output in a vendor-specific register.
	*/
	ac97->build_ops = &patch_yamaha_ymf753_ops;
	ac97->caps |= AC97_BC_BASS_TREBLE;
	ac97->caps |= 0x04 << 10; /* Yamaha 3D enhancement */
	return 0;
}