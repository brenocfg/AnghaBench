#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  size; TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_11__ {int tracks_add_done; int /*<<< orphan*/  null; int /*<<< orphan*/  moov_size; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_9__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BOX_TYPE_MOOV ; 
 int /*<<< orphan*/  STREAM_POSITION (TYPE_2__*) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ mp4_write_box (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_writer_extraio_disable (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_container_writer_extraio_enable (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_writer_add_track_done( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   if(module->tracks_add_done) return status;

   /* We need to find out the size of the object we're going to write it. */
   if(!vc_container_writer_extraio_enable(p_ctx, &module->null))
   {
      status = mp4_write_box(p_ctx, MP4_BOX_TYPE_MOOV);
      module->moov_size = STREAM_POSITION(p_ctx);
      p_ctx->size = module->moov_size;
   }
   vc_container_writer_extraio_disable(p_ctx, &module->null);

   if(status == VC_CONTAINER_SUCCESS) module->tracks_add_done = true;
   return status;
}