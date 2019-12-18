#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_1__* priv; int /*<<< orphan*/  tracks; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_21__ {scalar_t__ io; } ;
struct TYPE_20__ {TYPE_5__ null; void* data_offset; void* mdat_offset; int /*<<< orphan*/  temp; int /*<<< orphan*/  brand; int /*<<< orphan*/  tracks; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_18__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_write; int /*<<< orphan*/  pf_close; TYPE_3__* module; int /*<<< orphan*/  uri; } ;
typedef  int /*<<< orphan*/  MP4_BRAND_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  MP4_BOX_TYPE_FTYP ; 
 int /*<<< orphan*/  MP4_BRAND_3GP5 ; 
 int /*<<< orphan*/  MP4_BRAND_ISOM ; 
 int /*<<< orphan*/  MP4_BRAND_QT ; 
 int /*<<< orphan*/  MP4_BRAND_SKM2 ; 
 void* STREAM_POSITION (TYPE_2__*) ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  VC_FOURCC (char,char,char,char) ; 
 int /*<<< orphan*/  WRITE_FOURCC (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ mp4_write_box (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp4_writer_close ; 
 int /*<<< orphan*/  mp4_writer_control ; 
 int /*<<< orphan*/  mp4_writer_write ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 scalar_t__ vc_container_writer_extraio_create_null (TYPE_2__*,TYPE_5__*) ; 
 scalar_t__ vc_container_writer_extraio_create_temp (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_container_writer_extraio_delete (TYPE_2__*,TYPE_5__*) ; 
 int /*<<< orphan*/  vc_uri_find_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 char* vc_uri_path_extension (int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T mp4_writer_open( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   const char *extension = vc_uri_path_extension(p_ctx->priv->uri);
   VC_CONTAINER_MODULE_T *module = 0;
   MP4_BRAND_T brand;

   /* Check if the user has specified a container */
   vc_uri_find_query(p_ctx->priv->uri, 0, "container", &extension);

   /* Check we're the right writer for this */
   if(!extension)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   if(strcasecmp(extension, "3gp") && strcasecmp(extension, "skm") &&
      strcasecmp(extension, "mov") && strcasecmp(extension, "mp4") &&
      strcasecmp(extension, "m4v") && strcasecmp(extension, "m4a"))
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /* Allocate our context */
   module = malloc(sizeof(*module));
   if(!module) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(module, 0, sizeof(*module));
   p_ctx->priv->module = module;
   p_ctx->tracks = module->tracks;

   /* Find out which brand we're going write */
   if(!strcasecmp(extension, "3gp")) brand = MP4_BRAND_3GP5;
   else if(!strcasecmp(extension, "skm")) brand = MP4_BRAND_SKM2;
   else if(!strcasecmp(extension, "mov")) brand = MP4_BRAND_QT;
   else brand = MP4_BRAND_ISOM;
   module->brand = brand;

   /* Create a null i/o writer to help us out in writing our data */
   status = vc_container_writer_extraio_create_null(p_ctx, &module->null);
   if(status != VC_CONTAINER_SUCCESS) goto error;

   /* Create a temporary i/o writer to help us out in writing our data */
   status = vc_container_writer_extraio_create_temp(p_ctx, &module->temp);
   if(status != VC_CONTAINER_SUCCESS) goto error;

   status = mp4_write_box(p_ctx, MP4_BOX_TYPE_FTYP);
   if(status != VC_CONTAINER_SUCCESS) goto error;

   /* Start the mdat box */
   module->mdat_offset = STREAM_POSITION(p_ctx);
   WRITE_U32(p_ctx, 0, "size");
   WRITE_FOURCC(p_ctx, VC_FOURCC('m','d','a','t'), "type");
   module->data_offset = STREAM_POSITION(p_ctx);

   p_ctx->priv->pf_close = mp4_writer_close;
   p_ctx->priv->pf_write = mp4_writer_write;
   p_ctx->priv->pf_control = mp4_writer_control;
   return VC_CONTAINER_SUCCESS;

 error:
   LOG_DEBUG(p_ctx, "mp4: error opening stream");
   if(module)
   {
      if(module->null.io) vc_container_writer_extraio_delete(p_ctx, &module->null);
      free(module);
   }
   return status;
}