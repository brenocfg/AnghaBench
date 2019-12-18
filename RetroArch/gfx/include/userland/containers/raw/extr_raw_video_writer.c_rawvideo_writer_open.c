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
struct TYPE_9__ {TYPE_1__* priv; int /*<<< orphan*/ * tracks; } ;
typedef  TYPE_2__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_10__ {int yuv4mpeg2; int /*<<< orphan*/  track; } ;
typedef  TYPE_3__ VC_CONTAINER_MODULE_T ;
struct TYPE_8__ {int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_write; int /*<<< orphan*/  pf_close; TYPE_3__* module; int /*<<< orphan*/  uri; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rawvideo_writer_close ; 
 int /*<<< orphan*/  rawvideo_writer_control ; 
 int /*<<< orphan*/  rawvideo_writer_write ; 
 scalar_t__ strcasecmp (char const*,char*) ; 
 int /*<<< orphan*/  vc_uri_find_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 char* vc_uri_path_extension (int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T rawvideo_writer_open( VC_CONTAINER_T *ctx )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_FORMAT_INVALID;
   const char *extension = vc_uri_path_extension(ctx->priv->uri);
   VC_CONTAINER_MODULE_T *module;
   bool yuv4mpeg2 = false;

   /* Check if the user has specified a container */
   vc_uri_find_query(ctx->priv->uri, 0, "container", &extension);

   /* Check we're the right writer for this */
   if(!extension)
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;
   if(!strcasecmp(extension, "y4m") || !strcasecmp(extension, "yuv4mpeg2"))
      yuv4mpeg2 = true;
   if(!yuv4mpeg2 && strcasecmp(extension, "yuv"))
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   LOG_DEBUG(ctx, "using rawvideo writer");

   /* Allocate our context */
   module = malloc(sizeof(*module));
   if (!module) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(module, 0, sizeof(*module));
   ctx->priv->module = module;
   ctx->tracks = &module->track;
   module->yuv4mpeg2 = yuv4mpeg2;

   ctx->priv->pf_close = rawvideo_writer_close;
   ctx->priv->pf_write = rawvideo_writer_write;
   ctx->priv->pf_control = rawvideo_writer_control;
   return VC_CONTAINER_SUCCESS;

 error:
   LOG_DEBUG(ctx, "rawvideo: error opening stream (%i)", status);
   return status;
}