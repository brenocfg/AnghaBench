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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {scalar_t__ encoding; scalar_t__ pitch_den; scalar_t__ pitch_num; } ;

/* Variables and functions */
 scalar_t__ MMAL_ENCODING_UNKNOWN ; 
 TYPE_1__* pixel_pitch ; 

uint32_t mmal_encoding_stride_to_width(uint32_t encoding, uint32_t stride)
{
   unsigned int i;

   for(i = 0; pixel_pitch[i].encoding != MMAL_ENCODING_UNKNOWN; i++)
      if(pixel_pitch[i].encoding == encoding) break;

   if(pixel_pitch[i].encoding == MMAL_ENCODING_UNKNOWN)
      return 0;

   return pixel_pitch[i].pitch_den * stride / pixel_pitch[i].pitch_num;
}