#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {char* member_0; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_1__ string_pair_t ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;

/* Variables and functions */
#define  MMAL_ENCODING_H263 134 
#define  MMAL_ENCODING_H264 133 
#define  MMAL_ENCODING_MP2V 132 
#define  MMAL_ENCODING_MP4V 131 
#define  MMAL_ENCODING_VP6 130 
#define  MMAL_ENCODING_VP7 129 
#define  MMAL_ENCODING_VP8 128 
 int /*<<< orphan*/  parse_enum (int*,TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vcos_countof (TYPE_1__*) ; 

MMAL_STATUS_T mmal_parse_video_codec(uint32_t *dest, const char *str)
{
   static string_pair_t video_codec_enums[] = {
      { "h264",  MMAL_ENCODING_H264 },
      { "h263",  MMAL_ENCODING_H263 },
      { "mpeg4", MMAL_ENCODING_MP4V },
      { "mpeg2", MMAL_ENCODING_MP2V },
      { "vp8",   MMAL_ENCODING_VP8 },
      { "vp7",   MMAL_ENCODING_VP7 },
      { "vp6",   MMAL_ENCODING_VP6 },
   };
   int i = 0;
   MMAL_STATUS_T ret;

   ret = parse_enum(&i, video_codec_enums, vcos_countof(video_codec_enums), str);
   *dest = i;
   return ret;
}