#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_13__ {int tracks_num; int /*<<< orphan*/ * tracks; TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_14__ {int /*<<< orphan*/  null; int /*<<< orphan*/  temp; scalar_t__ mdat_offset; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_12__ {TYPE_3__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP4_BOX_TYPE_MOOV ; 
 int /*<<< orphan*/  SEEK (TYPE_2__*,scalar_t__) ; 
 scalar_t__ STREAM_POSITION (TYPE_2__*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  mp4_write_box (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_free_track (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_writer_extraio_delete (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_writer_close( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status;
   int64_t mdat_size;

   mdat_size = STREAM_POSITION(p_ctx) - module->mdat_offset;

   /* Write the moov box */
   status = mp4_write_box(p_ctx, MP4_BOX_TYPE_MOOV);

   /* Finalise the mdat box */
   SEEK(p_ctx, module->mdat_offset);
   WRITE_U32(p_ctx, (uint32_t)mdat_size, "mdat size" );

   for(; p_ctx->tracks_num > 0; p_ctx->tracks_num--)
      vc_container_free_track(p_ctx, p_ctx->tracks[p_ctx->tracks_num-1]);

   vc_container_writer_extraio_delete(p_ctx, &module->temp);
   vc_container_writer_extraio_delete(p_ctx, &module->null);
   free(module);

   return status;
}