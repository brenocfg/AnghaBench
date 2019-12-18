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
typedef  int /*<<< orphan*/  xenon_audio_t ;

/* Variables and functions */
 unsigned int SOUND_FREQUENCY ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  xenon_sound_init () ; 

__attribute__((used)) static void *xenon360_audio_init(const char *device,
      unsigned rate, unsigned latency,
      unsigned block_frames,
      unsigned *new_rate)
{
   static bool inited = false;

   if (!inited)
   {
      xenon_sound_init();
      inited = true;
   }

   *new_rate = SOUND_FREQUENCY;

   return calloc(1, sizeof(xenon_audio_t));
}