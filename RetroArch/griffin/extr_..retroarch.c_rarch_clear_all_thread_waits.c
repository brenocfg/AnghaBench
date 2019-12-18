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
 int /*<<< orphan*/  audio_driver_start (int) ; 
 int /*<<< orphan*/  audio_driver_stop () ; 

__attribute__((used)) static bool rarch_clear_all_thread_waits(unsigned clear_threads, void *data)
{
   if ( clear_threads > 0)
      audio_driver_start(false);
   else
      audio_driver_stop();

   return true;
}