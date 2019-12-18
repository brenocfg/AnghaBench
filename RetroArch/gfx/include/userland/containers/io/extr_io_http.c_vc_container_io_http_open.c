#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_8__ {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_control; int /*<<< orphan*/ * pf_write; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  (* pf_close ) (TYPE_1__*) ;int /*<<< orphan*/  uri_parts; TYPE_2__* module; int /*<<< orphan*/  uri; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
struct TYPE_9__ {int /*<<< orphan*/  header_list; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_MODULE_T ;
typedef  scalar_t__ VC_CONTAINER_IO_MODE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINERS_LIST_COMPARATOR_T ;
typedef  int /*<<< orphan*/  HTTP_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  HEADER_LIST_INITIAL_CAPACITY ; 
 scalar_t__ HTTP_URI_LENGTH_MAX ; 
 int /*<<< orphan*/  IO_HTTP_DEFAULT_PORT ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION ; 
 scalar_t__ VC_CONTAINER_ERROR_URI_OPEN_FAILED ; 
 int /*<<< orphan*/  VC_CONTAINER_IO_CAPS_NO_CACHING ; 
 int /*<<< orphan*/  VC_CONTAINER_IO_CAPS_SEEK_SLOW ; 
 scalar_t__ VC_CONTAINER_IO_MODE_WRITE ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (char const*) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 TYPE_2__* calloc (int,int) ; 
 int /*<<< orphan*/  io_http_close (TYPE_1__*) ; 
 int /*<<< orphan*/  io_http_control ; 
 scalar_t__ io_http_head (TYPE_1__*) ; 
 scalar_t__ io_http_header_comparator ; 
 scalar_t__ io_http_open_socket (TYPE_1__*) ; 
 int /*<<< orphan*/  io_http_read ; 
 int /*<<< orphan*/  io_http_seek ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_containers_list_create (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vc_uri_port (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_scheme (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_set_port (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T vc_container_io_http_open(VC_CONTAINER_IO_T *p_ctx,
   const char *unused, VC_CONTAINER_IO_MODE_T mode)
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_IO_MODULE_T *module = 0;
   VC_CONTAINER_PARAM_UNUSED(unused);

   /* Check the URI to see if we're dealing with an http stream */
   if (!vc_uri_scheme(p_ctx->uri_parts) ||
       strcasecmp(vc_uri_scheme(p_ctx->uri_parts), "http"))
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   /*
    * Some basic error checking.
    */

   if (mode == VC_CONTAINER_IO_MODE_WRITE)
   {
      status = VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION;
      goto error;
   }

   if (strlen(p_ctx->uri) > HTTP_URI_LENGTH_MAX)
   {
      status = VC_CONTAINER_ERROR_URI_OPEN_FAILED;
      goto error;
   }

   module = calloc(1, sizeof(*module));
   if (!module)
   {
      status = VC_CONTAINER_ERROR_OUT_OF_MEMORY;
      goto error;
   }
   p_ctx->module = module;

   /* header_list will contain pointers into the response_buffer, so take care in re-use */
   module->header_list = vc_containers_list_create(HEADER_LIST_INITIAL_CAPACITY, sizeof(HTTP_HEADER_T),
                                           (VC_CONTAINERS_LIST_COMPARATOR_T)io_http_header_comparator);
   if (!module->header_list)
   {
      status = VC_CONTAINER_ERROR_OUT_OF_MEMORY;
      goto error;
   }

   /*
    * Make sure that we have a port number.
    */

   if (vc_uri_port(p_ctx->uri_parts) == NULL)
      vc_uri_set_port(p_ctx->uri_parts, IO_HTTP_DEFAULT_PORT);

   status = io_http_open_socket(p_ctx);
   if (status != VC_CONTAINER_SUCCESS)
      goto error;

   /*
    * Whoo hoo! Our socket is open. Now let's send a HEAD request.
    */

   status = io_http_head(p_ctx);
   if (status != VC_CONTAINER_SUCCESS)
      goto error;

   p_ctx->pf_close   = io_http_close;
   p_ctx->pf_read    = io_http_read;
   p_ctx->pf_write   = NULL;
   p_ctx->pf_control = io_http_control;
   p_ctx->pf_seek    = io_http_seek;

   p_ctx->capabilities = VC_CONTAINER_IO_CAPS_NO_CACHING;
   p_ctx->capabilities |= VC_CONTAINER_IO_CAPS_SEEK_SLOW;

   return VC_CONTAINER_SUCCESS;

error:
   io_http_close(p_ctx);
   return status;
}