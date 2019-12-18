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
typedef  int u32 ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ DS_OK ; 
 scalar_t__ IDirectSoundBuffer8_GetCurrentPosition (int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  lpDSB2 ; 
 scalar_t__ soundbufsize ; 
 scalar_t__ soundoffset ; 

u32 SNDDXGetAudioSpace(void)
{
   DWORD playcursor, writecursor;
   u32 freespace=0;

   if (IDirectSoundBuffer8_GetCurrentPosition (lpDSB2, &playcursor, &writecursor) != DS_OK)
      return 0;

   if (soundoffset > playcursor)
      freespace = soundbufsize - soundoffset + playcursor;
   else
      freespace = playcursor - soundoffset;

//   if (freespace > 512)
      return (freespace / 2 / 2);
//   else
//      return 0;
}