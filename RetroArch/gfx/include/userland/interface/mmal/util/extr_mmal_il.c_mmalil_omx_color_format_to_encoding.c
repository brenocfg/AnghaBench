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
struct TYPE_2__ {scalar_t__ encoding; scalar_t__ coding; } ;
typedef  scalar_t__ OMX_COLOR_FORMATTYPE ;

/* Variables and functions */
 scalar_t__ MMAL_ENCODING_UNKNOWN ; 
 TYPE_1__* mmal_omx_colorformat_coding_table ; 

uint32_t mmalil_omx_color_format_to_encoding(OMX_COLOR_FORMATTYPE coding)
{
   unsigned int i;
   for(i = 0; mmal_omx_colorformat_coding_table[i].encoding != MMAL_ENCODING_UNKNOWN; i++)
      if(mmal_omx_colorformat_coding_table[i].coding == coding) break;
   return mmal_omx_colorformat_coding_table[i].encoding;
}