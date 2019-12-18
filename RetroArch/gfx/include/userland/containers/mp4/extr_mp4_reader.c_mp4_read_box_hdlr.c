#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int int64_t ;
struct TYPE_16__ {TYPE_2__* format; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_T ;
struct TYPE_17__ {TYPE_3__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_18__ {size_t current_track; scalar_t__ brand; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_ES_TYPE_T ;
struct TYPE_15__ {int /*<<< orphan*/  es_type; } ;
struct TYPE_14__ {TYPE_5__* module; } ;

/* Variables and functions */
 scalar_t__ MP4_BOX_TYPE_SOUN ; 
 scalar_t__ MP4_BOX_TYPE_TEXT ; 
 scalar_t__ MP4_BOX_TYPE_VIDE ; 
 scalar_t__ MP4_BRAND_QT ; 
 scalar_t__ MP4_READ_FOURCC (TYPE_4__*,char*) ; 
 scalar_t__ MP4_READ_U8 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_STRING (TYPE_4__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U24 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U32 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  MP4_SKIP_U8 (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_4__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ES_TYPE_AUDIO ; 
 int /*<<< orphan*/  VC_CONTAINER_ES_TYPE_SUBPICTURE ; 
 int /*<<< orphan*/  VC_CONTAINER_ES_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  VC_CONTAINER_ES_TYPE_VIDEO ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_read_box_hdlr( VC_CONTAINER_T *p_ctx, int64_t size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_T *track = p_ctx->tracks[module->current_track];
   uint32_t i, fourcc, string_size;
   VC_CONTAINER_ES_TYPE_T es_type = VC_CONTAINER_ES_TYPE_UNKNOWN;

   if(size <= 24) return VC_CONTAINER_ERROR_CORRUPTED;

   MP4_SKIP_U8(p_ctx, "version");
   MP4_SKIP_U24(p_ctx, "flags");

   MP4_SKIP_U32(p_ctx, "pre-defined");

   fourcc = MP4_READ_FOURCC(p_ctx, "handler_type");
   if(fourcc == MP4_BOX_TYPE_VIDE) es_type = VC_CONTAINER_ES_TYPE_VIDEO;
   if(fourcc == MP4_BOX_TYPE_SOUN) es_type = VC_CONTAINER_ES_TYPE_AUDIO;
   if(fourcc == MP4_BOX_TYPE_TEXT) es_type = VC_CONTAINER_ES_TYPE_SUBPICTURE;
   track->format->es_type = es_type;

   for(i = 0; i < 3; i++) MP4_SKIP_U32(p_ctx, "reserved");

   string_size = size;
   if(module->brand == MP4_BRAND_QT)
      string_size = MP4_READ_U8(p_ctx, "string_size");

   if(size < 0) return VC_CONTAINER_ERROR_CORRUPTED;
   if(string_size > size) string_size = size;

   MP4_SKIP_STRING(p_ctx, string_size, "name");

   return STREAM_STATUS(p_ctx);
}