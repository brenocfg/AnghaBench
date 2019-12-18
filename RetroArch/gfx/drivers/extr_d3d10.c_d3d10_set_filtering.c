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
struct TYPE_2__ {int /*<<< orphan*/ ** samplers; } ;
typedef  TYPE_1__ d3d10_video_t ;

/* Variables and functions */
 size_t RARCH_FILTER_LINEAR ; 
 size_t RARCH_FILTER_NEAREST ; 
 size_t RARCH_FILTER_UNSPEC ; 
 unsigned int RARCH_WRAP_MAX ; 

__attribute__((used)) static void d3d10_set_filtering(void* data, unsigned index, bool smooth)
{
   unsigned       i;
   d3d10_video_t* d3d10 = (d3d10_video_t*)data;

   for (i = 0; i < RARCH_WRAP_MAX; i++)
   {
      if (smooth)
         d3d10->samplers[RARCH_FILTER_UNSPEC][i] = d3d10->samplers[RARCH_FILTER_LINEAR][i];
      else
         d3d10->samplers[RARCH_FILTER_UNSPEC][i] = d3d10->samplers[RARCH_FILTER_NEAREST][i];
   }
}