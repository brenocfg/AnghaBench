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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  OMX_U32 ;

/* Variables and functions */
 int MMAL_BUFFER_HEADER_VIDEO_FLAG_INTERLACED ; 
 int MMAL_BUFFER_HEADER_VIDEO_FLAG_TOP_FIELD_FIRST ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_INTERLACED ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_TOP_FIELD_FIRST ; 

OMX_U32 mmalil_video_buffer_flags_to_omx(uint32_t flags)
{
   OMX_U32 omx_flags = 0;

   if (flags & MMAL_BUFFER_HEADER_VIDEO_FLAG_INTERLACED)
      omx_flags |= OMX_BUFFERFLAG_INTERLACED;
   if (flags & MMAL_BUFFER_HEADER_VIDEO_FLAG_TOP_FIELD_FIRST)
     omx_flags |= OMX_BUFFERFLAG_TOP_FIELD_FIRST;

  return omx_flags;
}