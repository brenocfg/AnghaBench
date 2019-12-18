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
 int MMAL_BUFFER_HEADER_FLAGS_SNAPSHOT ; 
 int MMAL_BUFFER_HEADER_FLAG_CODECSIDEINFO ; 
 int MMAL_BUFFER_HEADER_FLAG_CONFIG ; 
 int MMAL_BUFFER_HEADER_FLAG_CORRUPTED ; 
 int MMAL_BUFFER_HEADER_FLAG_DECODEONLY ; 
 int MMAL_BUFFER_HEADER_FLAG_DISCONTINUITY ; 
 int MMAL_BUFFER_HEADER_FLAG_EOS ; 
 int MMAL_BUFFER_HEADER_FLAG_FRAME_END ; 
 int MMAL_BUFFER_HEADER_FLAG_KEYFRAME ; 
 int MMAL_BUFFER_HEADER_FLAG_NAL_END ; 
 int MMAL_BUFFER_HEADER_FLAG_USER0 ; 
 int MMAL_BUFFER_HEADER_FLAG_USER1 ; 
 int MMAL_BUFFER_HEADER_FLAG_USER2 ; 
 int MMAL_BUFFER_HEADER_FLAG_USER3 ; 
 int MMAL_BUFFER_HEADER_VIDEO_FLAG_INTERLACED ; 
 int MMAL_BUFFER_HEADER_VIDEO_FLAG_TOP_FIELD_FIRST ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_CAPTURE_PREVIEW ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_CODECCONFIG ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_CODECSIDEINFO ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_DATACORRUPT ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_DECODEONLY ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_ENDOFFRAME ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_ENDOFNAL ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_EOS ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_INTERLACED ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_SYNCFRAME ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_TOP_FIELD_FIRST ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_USR0 ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_USR1 ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_USR2 ; 
 int /*<<< orphan*/  OMX_BUFFERFLAG_USR3 ; 

OMX_U32 mmalil_buffer_flags_to_omx(uint32_t flags)
{
   OMX_U32 omx_flags = 0;

   if(flags & MMAL_BUFFER_HEADER_FLAG_KEYFRAME)
      omx_flags |= OMX_BUFFERFLAG_SYNCFRAME;
   if(flags & MMAL_BUFFER_HEADER_FLAG_FRAME_END)
      omx_flags |= OMX_BUFFERFLAG_ENDOFFRAME;
   if(flags & MMAL_BUFFER_HEADER_FLAG_EOS)
      omx_flags |= OMX_BUFFERFLAG_EOS;
   if(flags & MMAL_BUFFER_HEADER_FLAG_CONFIG)
      omx_flags |= OMX_BUFFERFLAG_CODECCONFIG;
   if(flags & MMAL_BUFFER_HEADER_FLAG_DISCONTINUITY)
      omx_flags |= OMX_BUFFERFLAG_DISCONTINUITY;
   if (flags & MMAL_BUFFER_HEADER_FLAG_CODECSIDEINFO)
      omx_flags |= OMX_BUFFERFLAG_CODECSIDEINFO;
   if (flags & MMAL_BUFFER_HEADER_FLAGS_SNAPSHOT)
      omx_flags |= OMX_BUFFERFLAG_CAPTURE_PREVIEW;
   if (flags & MMAL_BUFFER_HEADER_FLAG_CORRUPTED)
      omx_flags |= OMX_BUFFERFLAG_DATACORRUPT;
   if (flags & MMAL_BUFFER_HEADER_FLAG_DECODEONLY)
      omx_flags |= OMX_BUFFERFLAG_DECODEONLY;
   if (flags & MMAL_BUFFER_HEADER_VIDEO_FLAG_INTERLACED)
      omx_flags |= OMX_BUFFERFLAG_INTERLACED;
   if (flags & MMAL_BUFFER_HEADER_VIDEO_FLAG_TOP_FIELD_FIRST)
     omx_flags |= OMX_BUFFERFLAG_TOP_FIELD_FIRST;
   if (flags & MMAL_BUFFER_HEADER_FLAG_NAL_END)
     omx_flags |= OMX_BUFFERFLAG_ENDOFNAL;

   if (flags & MMAL_BUFFER_HEADER_FLAG_USER0)
      omx_flags |= OMX_BUFFERFLAG_USR0;
   if (flags & MMAL_BUFFER_HEADER_FLAG_USER1)
      omx_flags |= OMX_BUFFERFLAG_USR1;
   if (flags & MMAL_BUFFER_HEADER_FLAG_USER2)
      omx_flags |= OMX_BUFFERFLAG_USR2;
   if (flags & MMAL_BUFFER_HEADER_FLAG_USER3)
      omx_flags |= OMX_BUFFERFLAG_USR3;

   return omx_flags;
}