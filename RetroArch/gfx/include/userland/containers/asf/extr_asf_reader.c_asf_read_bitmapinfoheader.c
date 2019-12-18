#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_13__ {TYPE_5__* format; TYPE_4__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_12__ {scalar_t__ codec; char* extradata; int /*<<< orphan*/  extradata_size; TYPE_2__* type; } ;
struct TYPE_11__ {TYPE_3__* module; } ;
struct TYPE_10__ {char* extradata; } ;
struct TYPE_8__ {void* height; void* width; } ;
struct TYPE_9__ {TYPE_1__ video; } ;

/* Variables and functions */
 int ASF_EXTRADATA_MAX ; 
 int /*<<< orphan*/  ASF_READ_BYTES (int /*<<< orphan*/ *,int,char*,int) ; 
 int ASF_READ_U16 (int /*<<< orphan*/ *,int,char*) ; 
 void* ASF_READ_U32 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U16 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U32 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ASF_SKIP_U8 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  LOG_FORMAT (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 scalar_t__ VC_CONTAINER_CODEC_UNKNOWN ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 scalar_t__ vfw_fourcc_to_codec (int) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_read_bitmapinfoheader( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_TRACK_T *p_track, int64_t size )
{
   uint32_t bmih_size, formatdata_size;
   uint32_t fourcc;

   /* Sanity check the size of the data */
   if(size < 40 + 11) return VC_CONTAINER_ERROR_CORRUPTED;

   /* Read the preamble to the BITMAPINFOHEADER */
   ASF_SKIP_U32(p_ctx, size, "Encoded Image Width");
   ASF_SKIP_U32(p_ctx, size, "Encoded Image Height");
   ASF_SKIP_U8(p_ctx, size, "Reserved Flags");
   formatdata_size = ASF_READ_U16(p_ctx, size, "Format Data Size");

   /* Sanity check the size of the data */
   if(formatdata_size < 40 || size < formatdata_size) return VC_CONTAINER_ERROR_CORRUPTED;
   bmih_size = ASF_READ_U32(p_ctx, size, "Format Data Size");
   if(bmih_size < 40 || bmih_size > formatdata_size) return VC_CONTAINER_ERROR_CORRUPTED;

   /* Read BITMAPINFOHEADER structure */
   p_track->format->type->video.width = ASF_READ_U32(p_ctx, size, "Image Width");
   p_track->format->type->video.height = ASF_READ_U32(p_ctx, size, "Image Height"); /* Signed */
   ASF_SKIP_U16(p_ctx, size, "Reserved");
   ASF_SKIP_U16(p_ctx, size, "Bits Per Pixel Count");
   ASF_READ_BYTES(p_ctx, size, (char *)&fourcc, 4); /* Compression ID */
   LOG_FORMAT(p_ctx, "Compression ID: %4.4s", (char *)&fourcc);
   p_track->format->codec = vfw_fourcc_to_codec(fourcc);
   if(p_track->format->codec == VC_CONTAINER_CODEC_UNKNOWN)
      p_track->format->codec = fourcc;
   ASF_SKIP_U32(p_ctx, size, "Image Size");
   ASF_SKIP_U32(p_ctx, size, "Horizontal Pixels Per Meter");
   ASF_SKIP_U32(p_ctx, size, "Vertical Pixels Per Meter");
   ASF_SKIP_U32(p_ctx, size, "Colors Used Count");
   ASF_SKIP_U32(p_ctx, size, "Important Colors Count");

   if(!(bmih_size -= 40))return VC_CONTAINER_SUCCESS;

   if(bmih_size > ASF_EXTRADATA_MAX)
   {
      LOG_DEBUG(p_ctx, "extradata truncated");
      bmih_size = ASF_EXTRADATA_MAX;
   }
   p_track->format->extradata = p_track->priv->module->extradata;
   p_track->format->extradata_size = ASF_READ_BYTES(p_ctx, size, p_track->format->extradata, bmih_size);

   return STREAM_STATUS(p_ctx);
}