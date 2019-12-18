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
struct TYPE_9__ {TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_10__ {scalar_t__ current_track; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_8__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  WRITE_U16 (TYPE_2__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U64 (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_write_object_ext_stream_properties( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;

   WRITE_U64(p_ctx, 0, "Start Time");
   WRITE_U64(p_ctx, 0, "End Time");
   WRITE_U32(p_ctx, 0, "Data Bitrate");
   WRITE_U32(p_ctx, 0, "Buffer Size");
   WRITE_U32(p_ctx, 0, "Initial Buffer Fullness");
   WRITE_U32(p_ctx, 0, "Alternate Data Bitrate");
   WRITE_U32(p_ctx, 0, "Alternate Buffer Size");
   WRITE_U32(p_ctx, 0, "Alternate Initial Buffer Fullness");
   WRITE_U32(p_ctx, 0, "Maximum Object Size");
   WRITE_U32(p_ctx, 0, "Flags");
   WRITE_U16(p_ctx, module->current_track + 1, "Stream Number");
   WRITE_U16(p_ctx, 0, "Stream Language ID Index");
   WRITE_U64(p_ctx, 0, "Average Time Per Frame");
   WRITE_U16(p_ctx, 0, "Stream Name Count");
   WRITE_U16(p_ctx, 0, "Payload Extension System Count");
   /* Stream Names */
   /* Payload Extension Systems */
   /* Stream Properties Object */

   return VC_CONTAINER_SUCCESS;
}