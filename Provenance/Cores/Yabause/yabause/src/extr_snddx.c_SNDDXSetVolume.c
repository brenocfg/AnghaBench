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
typedef  scalar_t__ LONG ;

/* Variables and functions */
 scalar_t__ DSBVOLUME_MIN ; 
 int /*<<< orphan*/  IDirectSoundBuffer8_SetVolume (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  issoundmuted ; 
 double log10 (double) ; 
 int /*<<< orphan*/  lpDSB2 ; 
 scalar_t__ soundvolume ; 

void SNDDXSetVolume(int volume)
{
   // Convert linear volume to logarithmic volume
   if (volume == 0)
      soundvolume = DSBVOLUME_MIN;
   else
      soundvolume = (LONG)(log10((double)volume / 100.0) * 2000.0);

   if (!issoundmuted)
      IDirectSoundBuffer8_SetVolume (lpDSB2, soundvolume);
}