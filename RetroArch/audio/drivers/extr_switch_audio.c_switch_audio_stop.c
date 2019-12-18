#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int is_paused; } ;
typedef  TYPE_1__ switch_audio_t ;

/* Variables and functions */
 scalar_t__ switch_audio_ipc_output_stop (TYPE_1__*) ; 

__attribute__((used)) static bool switch_audio_stop(void *data)
{
   switch_audio_t *swa = (switch_audio_t*) data;
   if (!swa)
      return false;

   /* TODO/FIXME - fix libnx codepath */
#ifndef HAVE_LIBNX

   if (!swa->is_paused)
	   if (switch_audio_ipc_output_stop(swa) != 0)
		   return false;

   swa->is_paused = true;
#endif
   return true;
}