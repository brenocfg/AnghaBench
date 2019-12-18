#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_18__ {int duration; scalar_t__ size; int /*<<< orphan*/  capabilities; TYPE_1__* priv; int /*<<< orphan*/  tracks_num; int /*<<< orphan*/  tracks; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_17__ {TYPE_2__* levels; } ;
struct TYPE_19__ {int duration; int timecode_scale; TYPE_3__ state; scalar_t__ tags_offset; scalar_t__ cues_offset; scalar_t__ cluster_offset; int /*<<< orphan*/  is_doctype_valid; int /*<<< orphan*/  elements_list; int /*<<< orphan*/  tracks; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
struct TYPE_16__ {scalar_t__ offset; } ;
struct TYPE_15__ {int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  (* pf_close ) (TYPE_4__*) ;TYPE_5__* module; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_C (int) ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_4__*,char*,scalar_t__) ; 
 int /*<<< orphan*/  MKV_ELEMENT_ID_SEGMENT ; 
 int /*<<< orphan*/  MKV_ELEMENT_ID_UNKNOWN ; 
 int PEEK_BYTES (TYPE_4__*,int*,int) ; 
 scalar_t__ SEEK (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  STREAM_SEEKABLE (TYPE_4__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_CAPS_CAN_SEEK ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_NO_TRACK_AVAILABLE ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 TYPE_5__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mkv_elements_list ; 
 scalar_t__ mkv_read_element (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkv_reader_close (TYPE_4__*) ; 
 int /*<<< orphan*/  mkv_reader_read ; 
 int /*<<< orphan*/  mkv_reader_seek ; 

VC_CONTAINER_STATUS_T mkv_reader_open(VC_CONTAINER_T *p_ctx)
{
   VC_CONTAINER_MODULE_T *module = 0;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_FORMAT_INVALID;
   uint8_t buffer[4];

   // Can start with ASCII strings ????

   /* Check for an EBML element */
   if(PEEK_BYTES(p_ctx, buffer, 4) < 4 ||
      buffer[0] != 0x1A || buffer[1] != 0x45 || buffer[2] != 0xDF || buffer[3] != 0xA3)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /*
    *  We are dealing with an MKV file
    */

   /* Allocate our context */
   module = malloc(sizeof(*module));
   if(!module) {status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error;}
   memset(module, 0, sizeof(*module));
   p_ctx->priv->module = module;
   p_ctx->tracks = module->tracks;
   module->elements_list = mkv_elements_list;

   /* Read and sanity check the EBML header */
   status = mkv_read_element(p_ctx, INT64_C(-1), MKV_ELEMENT_ID_UNKNOWN);
   if(status != VC_CONTAINER_SUCCESS) goto error;
   if(!module->is_doctype_valid) {status = VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED; goto error;}

   /* Read the other elements until we find the start of the data */
   do
   {
      status = mkv_read_element(p_ctx, INT64_C(-1), MKV_ELEMENT_ID_UNKNOWN);
      if(status != VC_CONTAINER_SUCCESS) break;

      if(module->cluster_offset) break;
   } while(1);

   /* Bail out if we didn't find a track */
   if(!p_ctx->tracks_num)
   {
      status = VC_CONTAINER_ERROR_NO_TRACK_AVAILABLE;
      goto error;
   }

   /*
    *  We now have all the information we really need to start playing the stream
    */

   p_ctx->priv->pf_close = mkv_reader_close;
   p_ctx->priv->pf_read = mkv_reader_read;
   p_ctx->priv->pf_seek = mkv_reader_seek;
   p_ctx->duration = module->duration / 1000 * module->timecode_scale;

   /* Check if we're done */
   if(!STREAM_SEEKABLE(p_ctx))
      return VC_CONTAINER_SUCCESS;

   if(module->cues_offset && (int64_t)module->cues_offset < p_ctx->size)
      p_ctx->capabilities |= VC_CONTAINER_CAPS_CAN_SEEK;

   if(module->tags_offset)
   {
      status = SEEK(p_ctx, module->tags_offset);
      if(status == VC_CONTAINER_SUCCESS)
         status = mkv_read_element(p_ctx, INT64_C(-1) /*FIXME*/, MKV_ELEMENT_ID_SEGMENT);
   }

   /* Seek back to the start of the data */
   return SEEK(p_ctx, module->state.levels[1].offset);

 error:
   LOG_DEBUG(p_ctx, "mkv: error opening stream (%i)", status);
   if(module) mkv_reader_close(p_ctx);
   return status;
}