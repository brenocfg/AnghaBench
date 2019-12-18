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
struct TYPE_3__ {char const* ident; } ;
typedef  TYPE_1__ retro_resampler_t ;

/* Variables and functions */
 TYPE_1__** resampler_drivers ; 

const char *audio_resampler_driver_find_ident(int idx)
{
   const retro_resampler_t *drv = resampler_drivers[idx];
   if (!drv)
      return NULL;
   return drv->ident;
}