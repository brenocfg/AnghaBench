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
struct TYPE_2__ {scalar_t__ coding; scalar_t__ index; } ;
typedef  scalar_t__ OMX_INDEXTYPE ;
typedef  scalar_t__ OMX_AUDIO_CODINGTYPE ;

/* Variables and functions */
 scalar_t__ OMX_AUDIO_CodingUnused ; 
 TYPE_1__* mmal_omx_audio_format_table ; 

OMX_AUDIO_CODINGTYPE mmalil_omx_audio_param_index_to_coding(OMX_INDEXTYPE index)
{
   unsigned int i;
   for(i = 0; mmal_omx_audio_format_table[i].coding != OMX_AUDIO_CodingUnused; i++)
      if(mmal_omx_audio_format_table[i].index == index) break;

   return mmal_omx_audio_format_table[i].coding;
}