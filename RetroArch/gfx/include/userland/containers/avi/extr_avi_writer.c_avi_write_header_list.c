#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_14__ {unsigned int tracks_num; TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_15__ {int /*<<< orphan*/  null_io; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_13__ {TYPE_3__* module; } ;

/* Variables and functions */
 scalar_t__ STREAM_POSITION (TYPE_2__*) ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_2__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  VC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  WRITE_FOURCC (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_2__*,scalar_t__,char*) ; 
 int /*<<< orphan*/  avi_write_avi_header_chunk (TYPE_2__*) ; 
 int /*<<< orphan*/  avi_write_stream_header_list (TYPE_2__*,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  vc_container_writer_extraio_disable (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_container_writer_extraio_enable (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_write_header_list( VC_CONTAINER_T *p_ctx, uint32_t header_list_size )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_STATUS_T status;
   unsigned int i;

   WRITE_FOURCC(p_ctx, VC_FOURCC('L','I','S','T'), "Chunk ID");
   WRITE_U32(p_ctx, header_list_size, "LIST Size");
   WRITE_FOURCC(p_ctx, VC_FOURCC('h','d','r','l'), "Chunk ID");
   if ((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS) return status;

   /* Write the main AVI header chunk ('avih') */
   if ((status = avi_write_avi_header_chunk(p_ctx)) != VC_CONTAINER_SUCCESS)
      return status;

   for (i = 0; i < p_ctx->tracks_num; i++)
   {
      uint32_t list_size = 0;

      /* Write a stream header list chunk ('strl') */
      if(!vc_container_writer_extraio_enable(p_ctx, &module->null_io))
      {
         status = avi_write_stream_header_list(p_ctx, i, 0);
         if (status != VC_CONTAINER_SUCCESS) return status;
         list_size = STREAM_POSITION(p_ctx) - 8;
      }
      vc_container_writer_extraio_disable(p_ctx, &module->null_io);

      status = avi_write_stream_header_list(p_ctx, i, list_size);
      if (status != VC_CONTAINER_SUCCESS) return status;
   }

   return status;
}