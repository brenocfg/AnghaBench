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
 int /*<<< orphan*/  RARCH_ERR (char*) ; 

__attribute__((used)) static void *null_audio_init(const char *device, unsigned rate, unsigned latency,
      unsigned block_frames,
      unsigned *new_rate)
{
   RARCH_ERR("Using the null audio driver. RetroArch will be silent.\n");

   (void)device;
   (void)rate;
   (void)latency;
   (void)new_rate;
   return (void*)-1;
}