#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__* tracks; TYPE_1__* priv; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_13__ {int /*<<< orphan*/  null; scalar_t__* tracks; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_11__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_write; int /*<<< orphan*/  pf_close; TYPE_3__* module; int /*<<< orphan*/  uri; } ;

/* Variables and functions */
 unsigned int ASF_TRACKS_MAX ; 
 int /*<<< orphan*/  LOG_DEBUG (TYPE_2__*,char*) ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  asf_writer_close ; 
 int /*<<< orphan*/  asf_writer_control ; 
 int /*<<< orphan*/  asf_writer_write ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  vc_container_free_track (TYPE_2__*,scalar_t__) ; 
 scalar_t__ vc_container_writer_extraio_create_null (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_find_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 char* vc_uri_path_extension (int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T asf_writer_open( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   const char *extension = vc_uri_path_extension(p_ctx->priv->uri);
   VC_CONTAINER_MODULE_T *module = 0;
   unsigned int i;

   /* Check if the user has specified a container */
   vc_uri_find_query(p_ctx->priv->uri, 0, "container", &extension);

   /* Check we're the right writer for this */
   if(!extension)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   if(strcasecmp(extension, "asf") && strcasecmp(extension, "wmv") &&
      strcasecmp(extension, "wma"))
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /* Allocate our context */
   module = malloc(sizeof(*module));
   if(!module) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(module, 0, sizeof(*module));
   p_ctx->priv->module = module;
   p_ctx->tracks = module->tracks;

   /* Create a null i/o writer to help us out in writing our data */
   status = vc_container_writer_extraio_create_null(p_ctx, &module->null);
   if(status != VC_CONTAINER_SUCCESS) goto error;

   /* We'll only write the header once we've got all our tracks */

   p_ctx->priv->pf_close = asf_writer_close;
   p_ctx->priv->pf_write = asf_writer_write;
   p_ctx->priv->pf_control = asf_writer_control;
   return VC_CONTAINER_SUCCESS;

 error:
   LOG_DEBUG(p_ctx, "asf: error opening stream");
   for(i = 0; i < ASF_TRACKS_MAX && p_ctx->tracks && p_ctx->tracks[i]; i++)
      vc_container_free_track(p_ctx, p_ctx->tracks[i]);
   free(module);
   return status;
}