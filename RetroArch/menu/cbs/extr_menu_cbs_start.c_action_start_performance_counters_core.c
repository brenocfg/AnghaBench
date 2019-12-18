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
struct retro_perf_counter {int dummy; } ;

/* Variables and functions */
 unsigned int MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_BEGIN ; 
 int generic_action_start_performance_counters (struct retro_perf_counter**,unsigned int,unsigned int,char const*) ; 
 struct retro_perf_counter** retro_get_perf_counter_libretro () ; 

__attribute__((used)) static int action_start_performance_counters_core(unsigned type, const char *label)
{
   struct retro_perf_counter **counters = retro_get_perf_counter_libretro();
   unsigned offset = type - MENU_SETTINGS_LIBRETRO_PERF_COUNTERS_BEGIN;

   return generic_action_start_performance_counters(counters, offset, type, label);
}