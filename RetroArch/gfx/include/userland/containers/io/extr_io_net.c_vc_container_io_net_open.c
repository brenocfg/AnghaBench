#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_5__ {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  pf_control; int /*<<< orphan*/  pf_write; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  (* pf_close ) (TYPE_1__*) ;int /*<<< orphan*/ * module; int /*<<< orphan*/  uri; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_IO_MODULE_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_IO_MODE_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_ERROR_URI_NOT_FOUND ; 
 int /*<<< orphan*/  VC_CONTAINER_IO_CAPS_CANT_SEEK ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (char const*) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  io_net_close (TYPE_1__*) ; 
 int /*<<< orphan*/  io_net_control ; 
 scalar_t__ io_net_open_socket (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  io_net_read ; 
 int /*<<< orphan*/  io_net_recognise_scheme (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  io_net_write ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

VC_CONTAINER_STATUS_T vc_container_io_net_open( VC_CONTAINER_IO_T *p_ctx,
   const char *unused, VC_CONTAINER_IO_MODE_T mode )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_IO_MODULE_T *module = 0;
   bool is_udp;
   VC_CONTAINER_PARAM_UNUSED(unused);

   if (!io_net_recognise_scheme(p_ctx->uri, &is_udp))
   { status = VC_CONTAINER_ERROR_URI_NOT_FOUND; goto error; }

   module = (VC_CONTAINER_IO_MODULE_T *)malloc( sizeof(*module) );
   if (!module) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(module, 0, sizeof(*module));
   p_ctx->module = module;

   status = io_net_open_socket(p_ctx, mode, is_udp);
   if (status != VC_CONTAINER_SUCCESS)
      goto error;

   p_ctx->pf_close = io_net_close;
   p_ctx->pf_read = io_net_read;
   p_ctx->pf_write = io_net_write;
   p_ctx->pf_control = io_net_control;

   /* Disable caching, as this will block waiting for enough data to fill the cache or an error */
   p_ctx->capabilities = VC_CONTAINER_IO_CAPS_CANT_SEEK;

   return VC_CONTAINER_SUCCESS;

error:
   io_net_close(p_ctx);
   return status;
}