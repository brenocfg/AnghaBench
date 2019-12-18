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
typedef  int /*<<< orphan*/  retro_resampler_t ;

/* Variables and functions */
 int find_resampler_driver_index (char const*) ; 
 int /*<<< orphan*/  const** resampler_drivers ; 

__attribute__((used)) static const retro_resampler_t *find_resampler_driver(const char *ident)
{
   int i = find_resampler_driver_index(ident);

   if (i >= 0)
      return resampler_drivers[i];

   return resampler_drivers[0];
}