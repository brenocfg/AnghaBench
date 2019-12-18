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
typedef  void ps2_audio_t ;

/* Variables and functions */
 int /*<<< orphan*/  audioConfigure (void*,unsigned int) ; 
 scalar_t__ calloc (int,int) ; 

__attribute__((used)) static void *ps2_audio_init(const char *device,
      unsigned rate, unsigned latency,
      unsigned block_frames,
      unsigned *new_rate)
{
   ps2_audio_t *ps2 = (ps2_audio_t*)calloc(1, sizeof(ps2_audio_t));

   if (!ps2)
      return NULL;

   audioConfigure(ps2, rate);

   return ps2;
}