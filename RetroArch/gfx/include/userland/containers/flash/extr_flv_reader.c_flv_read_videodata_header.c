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
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;

/* Variables and functions */
 int FLV_FLAG_INTERFRAME ; 
 int FLV_FLAG_KEYFRAME ; 
 int READ_U8 (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_H264 ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_SPARK ; 
 int /*<<< orphan*/  VC_CONTAINER_CODEC_VP6 ; 
 int /*<<< orphan*/  VC_FOURCC (char,char,char,char) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T flv_read_videodata_header(VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_FOURCC_T *codec, int *frame_type)
{
   uint8_t header = READ_U8(p_ctx, "FrameType/CodecID");

   if(frame_type)
      *frame_type = (header >> 4) == 1 ? FLV_FLAG_KEYFRAME :
         (header >> 4) == 3 ? FLV_FLAG_INTERFRAME : 0;

   switch(header &0xF)
   {
   case 2: *codec = VC_CONTAINER_CODEC_SPARK; break;
   case 3: *codec = VC_FOURCC('s','c','r','1'); break; /* screen video */
   case 4: *codec = VC_CONTAINER_CODEC_VP6; break;
   case 5: *codec = VC_FOURCC('v','p','6','a'); break; /* vp6 alpha */
   case 6: *codec = VC_FOURCC('s','c','r','2'); break; /* screen video 2 */
   case 7: *codec = VC_CONTAINER_CODEC_H264; break;
   default: *codec = 0; break;
   }

   return STREAM_STATUS(p_ctx);
}