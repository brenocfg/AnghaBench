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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int OMX_U32 ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_VIDEO_FLAG_INTERLACED ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_VIDEO_FLAG_TOP_FIELD_FIRST ; 
 int OMX_BUFFERFLAG_INTERLACED ; 
 int OMX_BUFFERFLAG_TOP_FIELD_FIRST ; 

uint32_t mmalil_video_buffer_flags_to_mmal(OMX_U32 flags)
{
   uint32_t mmal_flags = 0;

   if (flags & OMX_BUFFERFLAG_INTERLACED)
      mmal_flags |= MMAL_BUFFER_HEADER_VIDEO_FLAG_INTERLACED;
   if (flags & OMX_BUFFERFLAG_TOP_FIELD_FIRST)
      mmal_flags |= MMAL_BUFFER_HEADER_VIDEO_FLAG_TOP_FIELD_FIRST;

   return mmal_flags;
}