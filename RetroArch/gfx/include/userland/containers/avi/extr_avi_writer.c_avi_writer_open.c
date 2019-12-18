#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/ * tracks; scalar_t__ tracks_num; TYPE_2__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_15__ {scalar_t__ size; } ;
struct TYPE_18__ {struct TYPE_18__* avi_frame_buffer; int /*<<< orphan*/ * tracks; TYPE_1__ frame_packet; int /*<<< orphan*/  temp_io; int /*<<< orphan*/  null_io; } ;
typedef  TYPE_4__ VC_CONTAINER_MODULE_T ;
struct TYPE_16__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_write; int /*<<< orphan*/  pf_close; TYPE_4__* module; int /*<<< orphan*/  uri; } ;

/* Variables and functions */
 int AVI_FRAME_BUFFER_SIZE ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_3__*,char*) ; 
 scalar_t__ STREAM_SEEKABLE (TYPE_3__*) ; 
 scalar_t__ STREAM_STATUS (TYPE_3__*) ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  VC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  WRITE_FOURCC (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  avi_writer_close ; 
 int /*<<< orphan*/  avi_writer_control ; 
 int /*<<< orphan*/  avi_writer_write ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ vc_container_writer_extraio_create_null (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ vc_container_writer_extraio_create_temp (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_find_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 char* vc_uri_path_extension (int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T avi_writer_open( VC_CONTAINER_T *p_ctx )
{
   const char *extension = vc_uri_path_extension(p_ctx->priv->uri);
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_MODULE_T *module = 0;

   /* Check if the user has specified a container */
   vc_uri_find_query(p_ctx->priv->uri, 0, "container", &extension);

   /* Check we're the right writer for this */
   if(!extension)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   if(strcasecmp(extension, "avi") && strcasecmp(extension, "divx"))
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /* Allocate our context */
   module = malloc(sizeof(*module));
   if(!module) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(module, 0, sizeof(*module));
   p_ctx->priv->module = module;

   /* Create a null i/o writer to help us out in writing our data */
   status = vc_container_writer_extraio_create_null(p_ctx, &module->null_io);
   if(status != VC_CONTAINER_SUCCESS) goto error;

   if(STREAM_SEEKABLE(p_ctx))
   {
       /* Create a temporary i/o writer for storage of index data while we are writing */
       status = vc_container_writer_extraio_create_temp(p_ctx, &module->temp_io);
       if(status != VC_CONTAINER_SUCCESS) goto error;
   }
   else
   {
      module->avi_frame_buffer = malloc(AVI_FRAME_BUFFER_SIZE);
      if(!module->avi_frame_buffer)
         { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   }
   module->frame_packet.size = 0;

   p_ctx->tracks = module->tracks;

   /* Write the RIFF chunk descriptor */
   WRITE_FOURCC(p_ctx, VC_FOURCC('R','I','F','F'), "RIFF ID");
   WRITE_U32(p_ctx, 0, "fileSize");
   WRITE_FOURCC(p_ctx, VC_FOURCC('A','V','I',' '), "fileType");

   if((status = STREAM_STATUS(p_ctx)) != VC_CONTAINER_SUCCESS) goto error;

   p_ctx->priv->pf_close = avi_writer_close;
   p_ctx->priv->pf_write = avi_writer_write;
   p_ctx->priv->pf_control = avi_writer_control;

   return VC_CONTAINER_SUCCESS;

 error:
   LOG_DEBUG(p_ctx, "error opening stream");
   p_ctx->tracks_num = 0;
   p_ctx->tracks = NULL;
   if(module)
   {
      if(module->avi_frame_buffer) free(module->avi_frame_buffer);
      free(module);
   }
   return status;
}