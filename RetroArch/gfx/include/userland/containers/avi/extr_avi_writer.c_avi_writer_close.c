#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_25__ {int /*<<< orphan*/  max_chunk_size; scalar_t__ chunk_offs; int /*<<< orphan*/  chunk_index; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_26__ {unsigned int tracks_num; TYPE_9__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_28__ {scalar_t__ io; } ;
struct TYPE_27__ {size_t current_track_num; int data_offset; int header_list_offset; struct TYPE_27__* avi_frame_buffer; TYPE_7__ temp_io; TYPE_7__ null_io; scalar_t__ data_size; int /*<<< orphan*/  header_list_size; scalar_t__ index_status; scalar_t__ chunk_data_written; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
struct TYPE_29__ {TYPE_2__* priv; } ;
struct TYPE_24__ {TYPE_3__* module; } ;
struct TYPE_23__ {TYPE_5__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SEEK (TYPE_4__*,int) ; 
 scalar_t__ STREAM_POSITION (TYPE_4__*) ; 
 scalar_t__ STREAM_SEEKABLE (TYPE_4__*) ; 
 scalar_t__ STREAM_STATUS (TYPE_4__*) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_4__*,scalar_t__,char*) ; 
 scalar_t__ avi_finish_data_chunk (TYPE_4__*,scalar_t__) ; 
 scalar_t__ avi_write_header_list (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avi_write_index_entry (TYPE_4__*,size_t,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ avi_write_legacy_index_data (TYPE_4__*) ; 
 scalar_t__ avi_write_standard_index_data (TYPE_4__*) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  vc_container_free_track (TYPE_4__*,TYPE_9__*) ; 
 int /*<<< orphan*/  vc_container_writer_extraio_delete (TYPE_4__*,TYPE_7__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_writer_close( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   unsigned int i;

   /* If we arent't finished with a chunk we need to finish it first */
   if (module->chunk_data_written)
   {
      VC_CONTAINER_TRACK_MODULE_T *track_module = p_ctx->tracks[module->current_track_num]->priv->module;
      status = avi_finish_data_chunk(p_ctx, module->chunk_data_written);
      if (status != VC_CONTAINER_SUCCESS)
      {
         LOG_DEBUG(p_ctx, "warning, writing failed, last chunk truncated");
      }
      avi_write_index_entry(p_ctx, module->current_track_num, module->chunk_data_written, 0);
      track_module->chunk_index++;
      track_module->chunk_offs += module->chunk_data_written;
      track_module->max_chunk_size = MAX(track_module->max_chunk_size, module->chunk_data_written);
      module->chunk_data_written = 0;
   }

   if(STREAM_SEEKABLE(p_ctx))
   {
      uint32_t filesize;

      /* Write standard index data before finalising the size of the 'movi' list */
      status = avi_write_standard_index_data(p_ctx);
      if (status != VC_CONTAINER_SUCCESS)
      {
         module->index_status = status;
         LOG_DEBUG(p_ctx, "warning, writing standard index data failed, file will be malformed");
      }

      /* FIXME: support for multiple RIFF chunks (AVIX) */
      module->data_size = STREAM_POSITION(p_ctx) - module->data_offset - 8;

      /* Now write the legacy index */
      status = avi_write_legacy_index_data(p_ctx);
      if (status != VC_CONTAINER_SUCCESS)
      {
         module->index_status = status;
         LOG_DEBUG(p_ctx, "warning, writing legacy index data failed, file will be malformed");
      }

      /* If we can, do the necessary fixups for values not know at the
       time of writing chunk headers */

      /* Rewrite the AVI RIFF chunk size */
      filesize = (uint32_t)STREAM_POSITION(p_ctx);
      SEEK(p_ctx, 4);
      WRITE_U32(p_ctx, filesize, "fileSize");
      if(STREAM_STATUS(p_ctx) != VC_CONTAINER_SUCCESS)
      {
         LOG_DEBUG(p_ctx, "warning, rewriting 'fileSize' failed, file will be malformed");
      }

      /* Rewrite the header list chunk ('hdrl') */
      SEEK(p_ctx, module->header_list_offset);
      status = avi_write_header_list(p_ctx, module->header_list_size);
      if (status != VC_CONTAINER_SUCCESS)
      {
         LOG_DEBUG(p_ctx, "warning, rewriting 'hdrl' failed, file will be malformed");
      }

      /* Rewrite the AVI RIFF 'movi' list size */
      SEEK(p_ctx, module->data_offset + 4);
      WRITE_U32(p_ctx, module->data_size, "Chunk Size");
      if(STREAM_STATUS(p_ctx) != VC_CONTAINER_SUCCESS)
      {
         LOG_DEBUG(p_ctx, "warning, rewriting 'movi' list size failed, file will be malformed");
      }
   }

   vc_container_writer_extraio_delete(p_ctx, &module->null_io);
   if(module->temp_io.io) vc_container_writer_extraio_delete(p_ctx, &module->temp_io);

   for(i = 0; i < p_ctx->tracks_num; i++)
      vc_container_free_track(p_ctx, p_ctx->tracks[i]);
   p_ctx->tracks_num = 0;
   p_ctx->tracks = NULL;

   if(module->avi_frame_buffer) free(module->avi_frame_buffer);
   free(module);

   return status;
}