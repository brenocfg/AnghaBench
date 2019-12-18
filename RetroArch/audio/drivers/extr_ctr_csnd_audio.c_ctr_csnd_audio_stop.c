#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int playing; } ;
typedef  TYPE_1__ ctr_csnd_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  CSND_SetPlayState (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSND_SetVol (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csndExecCmds (int) ; 

__attribute__((used)) static bool ctr_csnd_audio_stop(void *data)
{
   ctr_csnd_audio_t* ctr = (ctr_csnd_audio_t*)data;

   /* using SetPlayState would make tracking the playback
    * position more difficult */

#if 0
   CSND_SetPlayState(0x8, 0);
   CSND_SetPlayState(0x9, 0);
#endif

   /* setting the channel volume to 0 seems to make it
    * impossible to set it back to full volume later */

   CSND_SetVol(0x8, 0x00000001, 0);
   CSND_SetVol(0x9, 0x00010000, 0);
   csndExecCmds(false);

   ctr->playing = false;

   return true;
}