#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_24__ {unsigned int tracks_num; int /*<<< orphan*/  capabilities; TYPE_4__* priv; TYPE_3__** tracks; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_25__ {int found_moov; scalar_t__ data_offset; int /*<<< orphan*/  data_size; TYPE_3__** tracks; } ;
typedef  TYPE_6__ VC_CONTAINER_MODULE_T ;
struct TYPE_23__ {int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  (* pf_close ) (TYPE_5__*) ;TYPE_6__* module; } ;
struct TYPE_22__ {TYPE_2__* priv; } ;
struct TYPE_21__ {TYPE_1__* module; } ;
struct TYPE_20__ {int /*<<< orphan*/  state; } ;
typedef  int const MP4_BOX_TYPE_T ;

/* Variables and functions */
 int /*<<< orphan*/  INT64_C (int) ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_5__*,char*) ; 
#define  MP4_BOX_TYPE_FREE 137 
#define  MP4_BOX_TYPE_FTYP 136 
#define  MP4_BOX_TYPE_MDAT 135 
#define  MP4_BOX_TYPE_MOOV 134 
#define  MP4_BOX_TYPE_PICT 133 
#define  MP4_BOX_TYPE_PNOT 132 
 int /*<<< orphan*/  MP4_BOX_TYPE_ROOT ; 
#define  MP4_BOX_TYPE_SKIP 131 
#define  MP4_BOX_TYPE_UDTA 130 
#define  MP4_BOX_TYPE_UUID 129 
#define  MP4_BOX_TYPE_WIDE 128 
 int PEEK_BYTES (TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ SEEK (TYPE_5__*,scalar_t__) ; 
 scalar_t__ STREAM_POSITION (TYPE_5__*) ; 
 scalar_t__ STREAM_SEEKABLE (TYPE_5__*) ; 
 scalar_t__ STREAM_STATUS (TYPE_5__*) ; 
 int /*<<< orphan*/  VC_CONTAINER_CAPS_CAN_SEEK ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int VC_FOURCC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mp4_read_box_data (TYPE_5__*,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mp4_read_box_header (TYPE_5__*,int /*<<< orphan*/ ,int const*,int /*<<< orphan*/ *) ; 
 scalar_t__ mp4_read_sample_header (TYPE_5__*,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp4_reader_close (TYPE_5__*) ; 
 int /*<<< orphan*/  mp4_reader_read ; 
 int /*<<< orphan*/  mp4_reader_seek ; 

VC_CONTAINER_STATUS_T mp4_reader_open( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   VC_CONTAINER_MODULE_T *module = 0;
   unsigned int i;
   uint8_t h[8];

   /* Check for a known box type to see if we're dealing with mp4 */
   if( PEEK_BYTES(p_ctx, h, 8) != 8 )
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   switch(VC_FOURCC(h[4],h[5],h[6],h[7]))
   {
   case MP4_BOX_TYPE_FTYP:
   case MP4_BOX_TYPE_MDAT:
   case MP4_BOX_TYPE_MOOV:
   case MP4_BOX_TYPE_FREE:
   case MP4_BOX_TYPE_SKIP:
   case MP4_BOX_TYPE_WIDE:
   case MP4_BOX_TYPE_PNOT:
   case MP4_BOX_TYPE_PICT:
   case MP4_BOX_TYPE_UDTA:
   case MP4_BOX_TYPE_UUID:
      break;
   default:
      /* Couldn't recognize the box type. This doesn't look like an mp4. */
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   }

   /*
    *  We are dealing with an MP4 file
    */

   LOG_DEBUG(p_ctx, "using mp4 reader");

   /* Allocate our context */
   module = malloc(sizeof(*module));
   if(!module) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(module, 0, sizeof(*module));
   p_ctx->priv->module = module;
   p_ctx->tracks = module->tracks;

   while(STREAM_STATUS(p_ctx) == VC_CONTAINER_SUCCESS)
   {
      MP4_BOX_TYPE_T box_type;
      int64_t box_size;

      status = mp4_read_box_header( p_ctx, INT64_C(-1), &box_type, &box_size );
      if(status != VC_CONTAINER_SUCCESS) goto error;

      if(box_type == MP4_BOX_TYPE_MDAT)
      {
         module->data_offset = STREAM_POSITION(p_ctx);
         module->data_size = box_size;
         if(module->found_moov) break; /* We've got everything we want */
      }
      else if(box_type == MP4_BOX_TYPE_MOOV)
         module->found_moov = true;

      status = mp4_read_box_data( p_ctx, box_type, box_size, MP4_BOX_TYPE_ROOT );
      if(status != VC_CONTAINER_SUCCESS) goto error;

      if(module->found_moov && module->data_offset) break; /* We've got everything we want */
   }

   /* Initialise tracks */
   for(i = 0; i < p_ctx->tracks_num; i++)
   {
      /* FIXME: we should check we've got at least one success */
      status = mp4_read_sample_header(p_ctx, i, &p_ctx->tracks[i]->priv->module->state);
   }

   status = SEEK(p_ctx, module->data_offset);
   if(status != VC_CONTAINER_SUCCESS) goto error;

   p_ctx->priv->pf_close = mp4_reader_close;
   p_ctx->priv->pf_read = mp4_reader_read;
   p_ctx->priv->pf_seek = mp4_reader_seek;

   if(STREAM_SEEKABLE(p_ctx))
      p_ctx->capabilities |= VC_CONTAINER_CAPS_CAN_SEEK;

   return VC_CONTAINER_SUCCESS;

 error:
   LOG_DEBUG(p_ctx, "mp4: error opening stream");
   if(module) mp4_reader_close(p_ctx);
   return status;
}