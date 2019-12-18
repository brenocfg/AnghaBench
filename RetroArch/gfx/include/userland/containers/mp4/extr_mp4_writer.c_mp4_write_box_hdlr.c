#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_15__ {TYPE_2__* format; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_T ;
struct TYPE_16__ {TYPE_3__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_17__ {size_t current_track; scalar_t__ brand; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
struct TYPE_14__ {scalar_t__ es_type; } ;
struct TYPE_13__ {TYPE_5__* module; } ;

/* Variables and functions */
 scalar_t__ MP4_BRAND_QT ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_4__*) ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_SUBPICTURE ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 int VC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  WRITE_FOURCC (TYPE_4__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_STRING (TYPE_4__*,char const*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U24 (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_4__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_4__*,int,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_hdlr( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_T *track = p_ctx->tracks[module->current_track];
   uint32_t i, handler_size, fourcc = 0;
   const char *handler_name;

   if(track->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO) fourcc = VC_FOURCC('v','i','d','e');
   if(track->format->es_type == VC_CONTAINER_ES_TYPE_AUDIO) fourcc = VC_FOURCC('s','o','u','n');
   if(track->format->es_type == VC_CONTAINER_ES_TYPE_SUBPICTURE) fourcc = VC_FOURCC('t','e','x','t');

   WRITE_U8(p_ctx,  0, "version");
   WRITE_U24(p_ctx, 0, "flags");

   if(module->brand == MP4_BRAND_QT)
      WRITE_FOURCC(p_ctx,  VC_FOURCC('m','h','l','r'), "component_type");
   else
      WRITE_U32(p_ctx,  0, "pre-defined");

   WRITE_FOURCC(p_ctx,  fourcc, "handler_type");
   for(i = 0; i < 3; i++)
      WRITE_U32(p_ctx,  0, "reserved");

   if(track->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO)
   { handler_name = "Video Media Handler"; handler_size = sizeof("Video Media Handler"); }
   else if(track->format->es_type == VC_CONTAINER_ES_TYPE_AUDIO)
   { handler_name = "Audio Media Handler"; handler_size = sizeof("Audio Media Handler"); }
   else if(track->format->es_type == VC_CONTAINER_ES_TYPE_SUBPICTURE)
   { handler_name = "Text Media Handler"; handler_size = sizeof("Text Media Handler"); }
   else { handler_name = ""; handler_size = sizeof(""); }

   if(module->brand == MP4_BRAND_QT)
   { handler_size--; WRITE_U8(p_ctx, handler_size, "string_size"); }

   WRITE_STRING(p_ctx, handler_name, handler_size, "name");

   return STREAM_STATUS(p_ctx);
}