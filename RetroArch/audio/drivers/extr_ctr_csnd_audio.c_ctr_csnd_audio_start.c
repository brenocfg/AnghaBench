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
 int /*<<< orphan*/  CSND_SetPlayState (int,int) ; 
 int /*<<< orphan*/  CSND_SetVol (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csndExecCmds (int) ; 

__attribute__((used)) static bool ctr_csnd_audio_start(void *data, bool is_shutdown)
{
   ctr_csnd_audio_t* ctr = (ctr_csnd_audio_t*)data;

   /* Prevents restarting audio when the menu
    * is toggled off on shutdown */
   if (is_shutdown)
      return true;

#if 0
   CSND_SetPlayState(0x8, 1);
   CSND_SetPlayState(0x9, 1);
#endif

   CSND_SetVol(0x8, 0x00008000, 0);
   CSND_SetVol(0x9, 0x80000000, 0);

   csndExecCmds(false);

   ctr->playing = true;

   return true;
}