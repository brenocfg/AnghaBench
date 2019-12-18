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
struct TYPE_2__ {scalar_t__ encoding; scalar_t__ bayer_order; scalar_t__ color_format; } ;
typedef  scalar_t__ OMX_COLOR_FORMATTYPE ;
typedef  scalar_t__ OMX_BAYERORDERTYPE ;

/* Variables and functions */
 scalar_t__ MMAL_ENCODING_UNKNOWN ; 
 TYPE_1__* mmal_omx_bayer_order_coding_table ; 

uint32_t mmalil_omx_bayer_format_order_to_encoding(OMX_BAYERORDERTYPE bayer_order, OMX_COLOR_FORMATTYPE color_format)
{
   unsigned int i;
   for(i = 0; mmal_omx_bayer_order_coding_table[i].encoding != MMAL_ENCODING_UNKNOWN; i++)
      if(mmal_omx_bayer_order_coding_table[i].bayer_order == bayer_order &&
         mmal_omx_bayer_order_coding_table[i].color_format == color_format)
         break;
   return mmal_omx_bayer_order_coding_table[i].encoding;
}