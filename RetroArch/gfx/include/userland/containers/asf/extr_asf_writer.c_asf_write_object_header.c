#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ tracks_num; TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_10__ {scalar_t__ current_track; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_8__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASF_OBJECT_TYPE_FILE_PROPS ; 
 int /*<<< orphan*/  ASF_OBJECT_TYPE_HEADER_EXT ; 
 int /*<<< orphan*/  ASF_OBJECT_TYPE_STREAM_PROPS ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  asf_write_object (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_write_object_header( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;

   WRITE_U32(p_ctx, 0, "Number of Header Objects"); /* FIXME: could use that */
   WRITE_U8(p_ctx, 0, "Reserved1");
   WRITE_U8(p_ctx, 0, "Reserved2");

   status = asf_write_object(p_ctx, ASF_OBJECT_TYPE_FILE_PROPS);
   status = asf_write_object(p_ctx, ASF_OBJECT_TYPE_HEADER_EXT);

   for(module->current_track = 0; module->current_track < p_ctx->tracks_num;
       module->current_track++)
   {
      status = asf_write_object(p_ctx, ASF_OBJECT_TYPE_STREAM_PROPS);
   }

   /* Codec List */
   /* Content Description */
   /* Stream Bitrate Properties */

   return status;
}