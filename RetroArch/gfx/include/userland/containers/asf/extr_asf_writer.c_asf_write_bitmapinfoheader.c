#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_9__ {TYPE_3__* format; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {int extradata_size; char* extradata; int /*<<< orphan*/  codec; TYPE_2__* type; } ;
struct TYPE_6__ {int width; int height; } ;
struct TYPE_7__ {TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_FORMAT (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  WRITE_BYTES (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  WRITE_U16 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  codec_to_fourcc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_write_bitmapinfoheader( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_TRACK_T *p_track )
{
   uint32_t fourcc;

   /* Write the preamble to the BITMAPINFOHEADER */
   WRITE_U32(p_ctx, p_track->format->type->video.width, "Encoded Image Width");
   WRITE_U32(p_ctx, p_track->format->type->video.height, "Encoded Image Height");
   WRITE_U8(p_ctx, 0, "Reserved Flags");
   WRITE_U16(p_ctx, 40 + p_track->format->extradata_size, "Format Data Size");

   /* Write BITMAPINFOHEADER structure */
   WRITE_U32(p_ctx, 40 + p_track->format->extradata_size, "Format Data Size");
   WRITE_U32(p_ctx, p_track->format->type->video.width, "Image Width");
   WRITE_U32(p_ctx, p_track->format->type->video.height, "Image Height");
   WRITE_U16(p_ctx, 0, "Reserved");
   WRITE_U16(p_ctx, 0, "Bits Per Pixel Count");
   fourcc = codec_to_fourcc(p_track->format->codec);
   WRITE_BYTES(p_ctx, (char *)&fourcc, 4); /* Compression ID */
   LOG_FORMAT(p_ctx, "Compression ID: %4.4s", (char *)&fourcc);
   WRITE_U32(p_ctx, 0, "Image Size");
   WRITE_U32(p_ctx, 0, "Horizontal Pixels Per Meter");
   WRITE_U32(p_ctx, 0, "Vertical Pixels Per Meter");
   WRITE_U32(p_ctx, 0, "Colors Used Count");
   WRITE_U32(p_ctx, 0, "Important Colors Count");

   WRITE_BYTES(p_ctx, p_track->format->extradata, p_track->format->extradata_size);

   return VC_CONTAINER_SUCCESS;
}