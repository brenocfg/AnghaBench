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
struct TYPE_2__ {scalar_t__ encoding; int /*<<< orphan*/  coding; } ;
typedef  int /*<<< orphan*/  OMX_IMAGE_CODINGTYPE ;

/* Variables and functions */
 scalar_t__ MMAL_ENCODING_UNKNOWN ; 
 TYPE_1__* mmal_omx_image_coding_table ; 

OMX_IMAGE_CODINGTYPE mmalil_encoding_to_omx_image_coding(uint32_t encoding)
{
   unsigned int i;
   for(i = 0; mmal_omx_image_coding_table[i].encoding != MMAL_ENCODING_UNKNOWN; i++)
      if(mmal_omx_image_coding_table[i].encoding == encoding) break;
   return mmal_omx_image_coding_table[i].coding;
}