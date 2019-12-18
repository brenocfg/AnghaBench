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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ DSBSTATUS_PLAYING ; 
 int /*<<< orphan*/  IDirectSound8_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSoundBuffer8_GetStatus (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  IDirectSoundBuffer8_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSoundBuffer8_Stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lpDS8 ; 
 int /*<<< orphan*/ * lpDSB ; 
 int /*<<< orphan*/ * lpDSB2 ; 

void SNDDXDeInit(void)
{
   DWORD status=0;

   if (lpDSB2)
   {
      IDirectSoundBuffer8_GetStatus(lpDSB2, &status);

      if(status == DSBSTATUS_PLAYING)
         IDirectSoundBuffer8_Stop(lpDSB2);

      IDirectSoundBuffer8_Release(lpDSB2);
      lpDSB2 = NULL;
   }

   if (lpDSB)
   {
      IDirectSoundBuffer8_Release(lpDSB);
      lpDSB = NULL;
   }

   if (lpDS8)
   {
      IDirectSound8_Release(lpDS8);
      lpDS8 = NULL;
   }
}