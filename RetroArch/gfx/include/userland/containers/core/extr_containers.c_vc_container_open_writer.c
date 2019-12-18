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
struct TYPE_12__ {TYPE_2__* priv; } ;
typedef  TYPE_1__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
typedef  void* VC_CONTAINER_PROGRESS_REPORT_FUNC_T ;
struct TYPE_13__ {int /*<<< orphan*/  uri; TYPE_3__* io; int /*<<< orphan*/  verbosity; } ;
typedef  TYPE_2__ VC_CONTAINER_PRIVATE_T ;
struct TYPE_14__ {scalar_t__ max_size; int /*<<< orphan*/  uri_parts; } ;
typedef  TYPE_3__ VC_CONTAINER_IO_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (TYPE_1__*,char*) ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  VC_CONTAINER_IO_MODE_WRITE ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (void*) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ WRITER_SPACE_SAFETY_MARGIN ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vc_container_close (TYPE_1__*) ; 
 int /*<<< orphan*/  vc_container_io_close (TYPE_3__*) ; 
 TYPE_3__* vc_container_io_open (char const*,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ vc_container_load_writer (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  vc_container_log_get_default_verbosity () ; 
 int /*<<< orphan*/  vc_uri_find_query (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const**) ; 
 char* vc_uri_path_extension (int /*<<< orphan*/ ) ; 

VC_CONTAINER_T *vc_container_open_writer( const char *uri, VC_CONTAINER_STATUS_T *p_status,
   VC_CONTAINER_PROGRESS_REPORT_FUNC_T pfn_progress, void *progress_userdata)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_T *p_ctx = 0;
   VC_CONTAINER_IO_T *io;
   const char *extension;
   VC_CONTAINER_PARAM_UNUSED(pfn_progress);
   VC_CONTAINER_PARAM_UNUSED(progress_userdata);

   /* Start by opening the URI */
   io = vc_container_io_open( uri, VC_CONTAINER_IO_MODE_WRITE, &status );
   if(!io) goto error;

   /* Make sure we have enough space available to start writing */
   if(io->max_size && io->max_size < WRITER_SPACE_SAFETY_MARGIN)
   {
      LOG_DEBUG(p_ctx, "not enough space available to open a writer");
      status = VC_CONTAINER_ERROR_OUT_OF_RESOURCES;
      goto error;
   }

   /* Allocate our context before trying out the different readers / writers */
   p_ctx = malloc( sizeof(*p_ctx) + sizeof(*p_ctx->priv));
   if(!p_ctx) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(p_ctx, 0, sizeof(*p_ctx) + sizeof(*p_ctx->priv));
   p_ctx->priv = (VC_CONTAINER_PRIVATE_T *)(p_ctx + 1);
   p_ctx->priv->verbosity = vc_container_log_get_default_verbosity();
   p_ctx->priv->io = io;
   p_ctx->priv->uri = io->uri_parts;
   io = NULL; /* io now owned by the context */

   /* If the uri has an extension, use it as a hint when loading the container */
   extension = vc_uri_path_extension(p_ctx->priv->uri);
   /* If the user has specified a container, then use that instead */
   vc_uri_find_query(p_ctx->priv->uri, 0, "container", &extension);

   status = vc_container_load_writer(p_ctx, extension);
   if(status != VC_CONTAINER_SUCCESS) goto error;

 end:
   if(p_status) *p_status = status;
   return p_ctx;

error:
   if(io) vc_container_io_close(io);
   if (p_ctx) vc_container_close(p_ctx);
   p_ctx = NULL;
   goto end;
}