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
 int /*<<< orphan*/  IDirectSoundBuffer8_SetVolume (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ issoundmuted ; 
 int /*<<< orphan*/  lpDSB2 ; 
 int /*<<< orphan*/  soundvolume ; 

void SNDDXUnMuteAudio(void)
{
   issoundmuted = 0;
   IDirectSoundBuffer8_SetVolume (lpDSB2, soundvolume);
}