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
typedef  int uint32_t ;
typedef  int int64_t ;
struct TYPE_19__ {int timescale; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_20__ {TYPE_3__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_21__ {size_t current_track; } ;
typedef  TYPE_6__ VC_CONTAINER_MODULE_T ;
struct TYPE_18__ {TYPE_2__* priv; } ;
struct TYPE_17__ {TYPE_4__* module; } ;
struct TYPE_16__ {TYPE_6__* module; } ;

/* Variables and functions */
 int MP4_READ_U32 (TYPE_5__*,char*) ; 
 int MP4_READ_U64 (TYPE_5__*,char*) ; 
 int MP4_READ_U8 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U16 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U24 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U32 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U64 (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_5__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_read_box_mdhd( VC_CONTAINER_T *p_ctx, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *track_module = p_ctx->tracks[module->current_track]->priv->module;
   uint32_t version, timescale;
   int64_t duration;

   version = MP4_READ_U8(p_ctx, "version");
   MP4_SKIP_U24(p_ctx, "flags");

   if(version)
   {
      MP4_SKIP_U64(p_ctx, "creation_time");
      MP4_SKIP_U64(p_ctx, "modification_time");
      timescale = MP4_READ_U32(p_ctx, "timescale");
      duration = MP4_READ_U64(p_ctx, "duration");
   }
   else
   {
      MP4_SKIP_U32(p_ctx, "creation_time");
      MP4_SKIP_U32(p_ctx, "modification_time");
      timescale = MP4_READ_U32(p_ctx, "timescale");
      duration = MP4_READ_U32(p_ctx, "duration");
   }

   if(timescale) duration = duration * 1000000 / timescale;
   track_module->timescale = timescale;

   MP4_SKIP_U16(p_ctx, "language"); /* ISO-639-2/T language code */
   MP4_SKIP_U16(p_ctx, "pre_defined");

   return STREAM_STATUS(p_ctx);
}