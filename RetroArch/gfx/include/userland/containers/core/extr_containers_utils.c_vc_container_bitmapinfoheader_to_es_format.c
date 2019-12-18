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
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  scalar_t__ VC_CONTAINER_FOURCC_T ;
struct TYPE_7__ {scalar_t__ codec; int /*<<< orphan*/  es_type; TYPE_2__* type; } ;
typedef  TYPE_3__ VC_CONTAINER_ES_FORMAT_T ;
struct TYPE_5__ {int width; int height; } ;
struct TYPE_6__ {TYPE_1__ video; } ;

/* Variables and functions */
 unsigned int BITMAPINFOHEADER_SIZE_MAX ; 
 scalar_t__ VC_CONTAINER_CODEC_UNKNOWN ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  VC_CONTAINER_ES_TYPE_VIDEO ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 scalar_t__ fourcc_to_codec (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,int*,int) ; 
 scalar_t__ vfw_fourcc_to_codec (scalar_t__) ; 

VC_CONTAINER_STATUS_T vc_container_bitmapinfoheader_to_es_format(uint8_t *p,
   unsigned int buffer_size, unsigned int *extra_offset, unsigned int *extra_size,
   VC_CONTAINER_ES_FORMAT_T *format)
{
   VC_CONTAINER_FOURCC_T fourcc;

   if(!p || buffer_size < BITMAPINFOHEADER_SIZE_MAX) return VC_CONTAINER_ERROR_INVALID_ARGUMENT;
   /* size = (p[3] << 24) | (p[2] << 16) | (p[1] << 8) | p[0]; */
   format->type->video.width = (p[7] << 24) | (p[6] << 16) | (p[5] << 8) | p[4];
   format->type->video.height = (p[11] << 24) | (p[10] << 16) | (p[9] << 8) | p[8];
   memcpy(&fourcc, p + 16, 4);

   format->es_type = VC_CONTAINER_ES_TYPE_VIDEO;
   format->codec = vfw_fourcc_to_codec(fourcc);

   /* If no mapping is found from vfw, try a more generic one */
   if (format->codec == fourcc && (fourcc = fourcc_to_codec(fourcc)) != VC_CONTAINER_CODEC_UNKNOWN)
      format->codec = fourcc;

   if(extra_offset) *extra_offset = BITMAPINFOHEADER_SIZE_MAX;
   if(extra_size)
   {
      if (buffer_size > BITMAPINFOHEADER_SIZE_MAX)
         *extra_size = buffer_size - BITMAPINFOHEADER_SIZE_MAX;
      else
         *extra_size = 0;
   }

   return VC_CONTAINER_SUCCESS;
}