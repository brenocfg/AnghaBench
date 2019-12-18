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
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;

/* Variables and functions */
#define  AV_CODEC_ID_MJPEG 131 
#define  AV_CODEC_ID_PNG 130 
#define  CODEC_ID_MJPEG 129 
#define  CODEC_ID_PNG 128 

__attribute__((used)) static bool codec_is_image(enum AVCodecID id)
{
   switch (id)
   {
#ifdef OLD_FFMPEG_API
      case CODEC_ID_MJPEG:
      case CODEC_ID_PNG:
#else
      case AV_CODEC_ID_MJPEG:
      case AV_CODEC_ID_PNG:
#endif
         return true;

      default:
         break;
   }

   return false;
}