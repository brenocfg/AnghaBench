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
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAGS_SNAPSHOT ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_CODECSIDEINFO ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_CONFIG ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_CORRUPTED ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_DECODEONLY ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_EOS ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_FRAME_END ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_KEYFRAME ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_NAL_END ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_USER0 ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_USER1 ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_USER2 ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_FLAG_USER3 ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_VIDEO_FLAG_INTERLACED ; 
 int /*<<< orphan*/  MMAL_BUFFER_HEADER_VIDEO_FLAG_TOP_FIELD_FIRST ; 
 int OMX_BUFFERFLAG_CAPTURE_PREVIEW ; 
 int OMX_BUFFERFLAG_CODECCONFIG ; 
 int OMX_BUFFERFLAG_CODECSIDEINFO ; 
 int OMX_BUFFERFLAG_DATACORRUPT ; 
 int OMX_BUFFERFLAG_DECODEONLY ; 
 int OMX_BUFFERFLAG_DISCONTINUITY ; 
 int OMX_BUFFERFLAG_ENDOFFRAME ; 
 int OMX_BUFFERFLAG_ENDOFNAL ; 
 int OMX_BUFFERFLAG_EOS ; 
 int OMX_BUFFERFLAG_INTERLACED ; 
 int OMX_BUFFERFLAG_SYNCFRAME ; 
 int OMX_BUFFERFLAG_TOP_FIELD_FIRST ; 
 int OMX_BUFFERFLAG_USR0 ; 
 int OMX_BUFFERFLAG_USR1 ; 
 int OMX_BUFFERFLAG_USR2 ; 
 int OMX_BUFFERFLAG_USR3 ; 

uint32_t mmalil_buffer_flags_to_mmal(OMX_U32 flags)
{
   uint32_t mmal_flags = 0;

   if (flags & OMX_BUFFERFLAG_SYNCFRAME)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_KEYFRAME;
   if (flags & OMX_BUFFERFLAG_ENDOFFRAME)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_FRAME_END;
   if (flags & OMX_BUFFERFLAG_EOS)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_EOS;
   if (flags & OMX_BUFFERFLAG_CODECCONFIG)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_CONFIG;
   if (flags & OMX_BUFFERFLAG_DISCONTINUITY)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_DISCONTINUITY;
   if (flags & OMX_BUFFERFLAG_CODECSIDEINFO)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_CODECSIDEINFO;
   if (flags & OMX_BUFFERFLAG_CAPTURE_PREVIEW)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAGS_SNAPSHOT;
   if (flags & OMX_BUFFERFLAG_DATACORRUPT)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_CORRUPTED;
   if (flags & OMX_BUFFERFLAG_DECODEONLY)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_DECODEONLY;
   if (flags & OMX_BUFFERFLAG_INTERLACED)
      mmal_flags |= MMAL_BUFFER_HEADER_VIDEO_FLAG_INTERLACED;
   if (flags & OMX_BUFFERFLAG_TOP_FIELD_FIRST)
      mmal_flags |= MMAL_BUFFER_HEADER_VIDEO_FLAG_TOP_FIELD_FIRST;
   if (flags & OMX_BUFFERFLAG_ENDOFNAL)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_NAL_END;

   if (flags & OMX_BUFFERFLAG_USR0)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_USER0;
   if (flags & OMX_BUFFERFLAG_USR1)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_USER1;
   if (flags & OMX_BUFFERFLAG_USR2)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_USER2;
   if (flags & OMX_BUFFERFLAG_USR3)
      mmal_flags |= MMAL_BUFFER_HEADER_FLAG_USER3;

   return mmal_flags;
}