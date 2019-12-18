#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_19__ {TYPE_3__* priv; int /*<<< orphan*/  format; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_T ;
struct TYPE_20__ {size_t tracks_num; TYPE_4__** tracks; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_21__ {int flags; int codec; int /*<<< orphan*/  extradata_size; scalar_t__ codec_variant; } ;
typedef  TYPE_6__ VC_CONTAINER_ES_FORMAT_T ;
struct TYPE_18__ {TYPE_2__* module; } ;
struct TYPE_17__ {int offset; TYPE_1__* sample_table; scalar_t__ fourcc; } ;
struct TYPE_16__ {int entry_size; } ;

/* Variables and functions */
 size_t MP4_SAMPLE_TABLE_CO64 ; 
 size_t MP4_SAMPLE_TABLE_CTTS ; 
 size_t MP4_SAMPLE_TABLE_STCO ; 
 size_t MP4_SAMPLE_TABLE_STSC ; 
 size_t MP4_SAMPLE_TABLE_STSS ; 
 size_t MP4_SAMPLE_TABLE_STSZ ; 
 size_t MP4_SAMPLE_TABLE_STTS ; 
 size_t MP4_TRACKS_MAX ; 
#define  VC_CONTAINER_CODEC_AMRNB 142 
#define  VC_CONTAINER_CODEC_AMRWB 141 
#define  VC_CONTAINER_CODEC_AMRWBP 140 
#define  VC_CONTAINER_CODEC_EVRC 139 
#define  VC_CONTAINER_CODEC_H263 138 
#define  VC_CONTAINER_CODEC_H264 137 
#define  VC_CONTAINER_CODEC_JPEG 136 
#define  VC_CONTAINER_CODEC_MJPEG 135 
#define  VC_CONTAINER_CODEC_MJPEGA 134 
#define  VC_CONTAINER_CODEC_MJPEGB 133 
#define  VC_CONTAINER_CODEC_MP1V 132 
#define  VC_CONTAINER_CODEC_MP2V 131 
#define  VC_CONTAINER_CODEC_MP4A 130 
#define  VC_CONTAINER_CODEC_MP4V 129 
#define  VC_CONTAINER_CODEC_MPGA 128 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_RESOURCES ; 
 scalar_t__ VC_CONTAINER_ERROR_TRACK_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION ; 
 int VC_CONTAINER_ES_FORMAT_FLAG_FRAMED ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ VC_FOURCC (char,char,char,char) ; 
 TYPE_4__* vc_container_allocate_track (TYPE_5__*,int) ; 
 int /*<<< orphan*/  vc_container_format_copy (int /*<<< orphan*/ ,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_free_track (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ vc_container_track_allocate_extradata (TYPE_5__*,TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_writer_add_track( VC_CONTAINER_T *p_ctx, VC_CONTAINER_ES_FORMAT_T *format )
{
   VC_CONTAINER_STATUS_T status;
   VC_CONTAINER_TRACK_T *track;
   uint32_t type = 0;

   if(!(format->flags & VC_CONTAINER_ES_FORMAT_FLAG_FRAMED))
      return VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION;

   /* Check we support this format */
   switch(format->codec)
   {
   case VC_CONTAINER_CODEC_AMRNB:  type = VC_FOURCC('s','a','m','r'); break;
   case VC_CONTAINER_CODEC_AMRWB:  type = VC_FOURCC('s','a','w','b'); break;
   case VC_CONTAINER_CODEC_AMRWBP: type = VC_FOURCC('s','a','w','p'); break;
   case VC_CONTAINER_CODEC_EVRC:   type = VC_FOURCC('s','e','v','c'); break;
   case VC_CONTAINER_CODEC_MP4A:   type = VC_FOURCC('m','p','4','a'); break;
   case VC_CONTAINER_CODEC_MPGA:   type = VC_FOURCC('m','p','4','a'); break;

   case VC_CONTAINER_CODEC_MP4V:   type = VC_FOURCC('m','p','4','v'); break;
   case VC_CONTAINER_CODEC_JPEG:   type = VC_FOURCC('m','p','4','v'); break;
   case VC_CONTAINER_CODEC_H263:   type = VC_FOURCC('s','2','6','3'); break;
   case VC_CONTAINER_CODEC_H264:
      if(format->codec_variant == VC_FOURCC('a','v','c','C')) type = VC_FOURCC('a','v','c','1'); break;
   case VC_CONTAINER_CODEC_MJPEG:  type = VC_FOURCC('j','p','e','g'); break;
   case VC_CONTAINER_CODEC_MJPEGA: type = VC_FOURCC('m','j','p','a'); break;
   case VC_CONTAINER_CODEC_MJPEGB: type = VC_FOURCC('m','j','p','b'); break;
   case VC_CONTAINER_CODEC_MP1V:   type = VC_FOURCC('m','p','e','g'); break;
   case VC_CONTAINER_CODEC_MP2V:   type = VC_FOURCC('m','p','e','g'); break;

   default: type = 0; break;
   }

   if(!type) return VC_CONTAINER_ERROR_TRACK_FORMAT_NOT_SUPPORTED;

   /* Allocate and initialise track data */
   if(p_ctx->tracks_num >= MP4_TRACKS_MAX) return VC_CONTAINER_ERROR_OUT_OF_RESOURCES;
   p_ctx->tracks[p_ctx->tracks_num] = track =
      vc_container_allocate_track(p_ctx, sizeof(*p_ctx->tracks[0]->priv->module));
   if(!track) return VC_CONTAINER_ERROR_OUT_OF_MEMORY;

   if(format->extradata_size)
   {
      status = vc_container_track_allocate_extradata( p_ctx, track, format->extradata_size );
      if(status) goto error;
   }

   vc_container_format_copy(track->format, format, format->extradata_size);
   track->priv->module->fourcc = type;
   track->priv->module->offset = -1;
   track->priv->module->sample_table[MP4_SAMPLE_TABLE_STTS].entry_size = 8;
   track->priv->module->sample_table[MP4_SAMPLE_TABLE_STSZ].entry_size = 4;
   track->priv->module->sample_table[MP4_SAMPLE_TABLE_STSC].entry_size = 12;
   track->priv->module->sample_table[MP4_SAMPLE_TABLE_STCO].entry_size = 4;
   track->priv->module->sample_table[MP4_SAMPLE_TABLE_STSS].entry_size = 4;
   track->priv->module->sample_table[MP4_SAMPLE_TABLE_CO64].entry_size = 8;
   track->priv->module->sample_table[MP4_SAMPLE_TABLE_CTTS].entry_size = 8;

   p_ctx->tracks_num++;
   return VC_CONTAINER_SUCCESS;

 error:
   vc_container_free_track(p_ctx, track);
   return status;
}