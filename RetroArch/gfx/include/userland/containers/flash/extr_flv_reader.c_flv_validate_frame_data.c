#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int32_t ;
struct TYPE_9__ {TYPE_2__** tracks; scalar_t__ tracks_num; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {TYPE_1__* format; } ;
struct TYPE_7__ {int codec; } ;

/* Variables and functions */
#define  VC_CONTAINER_CODEC_H264 130 
#define  VC_CONTAINER_CODEC_MP4A 129 
#define  VC_CONTAINER_CODEC_VP6 128 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CONTINUE ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int _READ_U24 (TYPE_3__*) ; 
 int _READ_U8 (TYPE_3__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T flv_validate_frame_data(VC_CONTAINER_T *p_ctx,
   int track, int *p_size, uint32_t *p_timestamp)
{
   int32_t time_offset;

   if(track >= (int)p_ctx->tracks_num)
      return *p_size ? VC_CONTAINER_SUCCESS : VC_CONTAINER_ERROR_CONTINUE;

   switch(p_ctx->tracks[track]->format->codec)
   {
   case VC_CONTAINER_CODEC_VP6:
      if(*p_size < 1) return VC_CONTAINER_ERROR_CORRUPTED;
      _READ_U8(p_ctx); *p_size -= 1;
      break;
   case VC_CONTAINER_CODEC_MP4A:
      if(*p_size < 1) return VC_CONTAINER_ERROR_CORRUPTED;
      *p_size -= 1;
      if(_READ_U8(p_ctx)!=1) return VC_CONTAINER_ERROR_CONTINUE; /* empty frame*/
      break;
   case VC_CONTAINER_CODEC_H264:
      if(*p_size < 4) return VC_CONTAINER_ERROR_CORRUPTED;
      *p_size -= 1;
      if(_READ_U8(p_ctx)!=1) return VC_CONTAINER_ERROR_CONTINUE; /* empty frame*/
      time_offset = _READ_U24(p_ctx);
      time_offset <<= 8; time_offset >>= 8; /* change to signed */
      *p_timestamp += time_offset;
      *p_size -= 3;
      break;
   default:
      break;
   }

   return *p_size ? VC_CONTAINER_SUCCESS : VC_CONTAINER_ERROR_CONTINUE;
}