#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ uint32_t ;
struct TYPE_7__ {int extradata_size; scalar_t__ es_type; scalar_t__* extradata; TYPE_2__* type; int /*<<< orphan*/  codec; } ;
typedef  TYPE_3__ VC_CONTAINER_ES_FORMAT_T ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_6__ {TYPE_1__ video; } ;

/* Variables and functions */
 int BITMAPINFOHEADER_SIZE_MAX ; 
 scalar_t__ VC_CONTAINER_CODEC_UNKNOWN ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 scalar_t__ codec_to_vfw_fourcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 

unsigned int vc_container_es_format_to_bitmapinfoheader(VC_CONTAINER_ES_FORMAT_T *format,
                                                        uint8_t *buffer, unsigned int buffer_size)
{
   uint32_t fourcc = codec_to_vfw_fourcc(format->codec);
   uint32_t size = BITMAPINFOHEADER_SIZE_MAX + format->extradata_size;

   if(format->es_type != VC_CONTAINER_ES_TYPE_VIDEO ||
      fourcc == VC_CONTAINER_CODEC_UNKNOWN) return 0;

   if(!buffer) return size;
   if(buffer_size < size) return 0;

   /* Build a bitmapinfoheader header */
   memset(buffer, 0, BITMAPINFOHEADER_SIZE_MAX);
   buffer[0] = (size >> 0) & 0xFF;
   buffer[1] = (size >> 8) & 0xFF;
   buffer[2] = (size >> 16) & 0xFF;
   buffer[3] = (size >> 24) & 0xFF;
   buffer[4] = (format->type->video.width >> 0) & 0xFF;
   buffer[5] = (format->type->video.width >> 8) & 0xFF;
   buffer[6] = (format->type->video.width >> 16) & 0xFF;
   buffer[7] = (format->type->video.width >> 24) & 0xFF;
   buffer[8] = (format->type->video.height >> 0) & 0xFF;
   buffer[9] = (format->type->video.height >> 8) & 0xFF;
   buffer[10] = (format->type->video.height >> 16) & 0xFF;
   buffer[11] = (format->type->video.height >> 24) & 0xFF;
   memcpy(buffer + 16, &fourcc, 4);
   memcpy(buffer + BITMAPINFOHEADER_SIZE_MAX, format->extradata, format->extradata_size);
   return size;
}