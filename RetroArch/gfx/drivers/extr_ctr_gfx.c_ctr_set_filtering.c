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
struct TYPE_2__ {int smooth; } ;
typedef  TYPE_1__ ctr_video_t ;

/* Variables and functions */

__attribute__((used)) static void ctr_set_filtering(void* data, unsigned index, bool smooth)
{
   ctr_video_t* ctr = (ctr_video_t*)data;

   if (ctr)
      ctr->smooth = smooth;
}