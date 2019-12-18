#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_7__ {int /*<<< orphan*/  capabilities; int /*<<< orphan*/  pf_write; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  pf_close; TYPE_2__* module; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
struct TYPE_8__ {int is_native_order; int /*<<< orphan*/ * stream; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_MODULE_T ;
typedef  scalar_t__ VC_CONTAINER_IO_MODE_T ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_IO_CAPS_CANT_SEEK ; 
 scalar_t__ VC_CONTAINER_IO_MODE_WRITE ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (char const*) ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  io_pktfile_close ; 
 int /*<<< orphan*/  io_pktfile_read ; 
 int /*<<< orphan*/  io_pktfile_write ; 
 TYPE_2__* malloc (int) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * open_file (TYPE_1__*,scalar_t__,scalar_t__*) ; 
 scalar_t__ read_byte_order (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ write_byte_order (int /*<<< orphan*/ *) ; 

VC_CONTAINER_STATUS_T vc_container_io_pktfile_open( VC_CONTAINER_IO_T *p_ctx,
   const char *unused, VC_CONTAINER_IO_MODE_T mode )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;
   VC_CONTAINER_IO_MODULE_T *module = 0;
   FILE *stream = 0;
   bool is_native_order = true;
   VC_CONTAINER_PARAM_UNUSED(unused);

   stream = open_file(p_ctx, mode, &status);
   if (status != VC_CONTAINER_SUCCESS) goto error;

   if (mode == VC_CONTAINER_IO_MODE_WRITE)
      status = write_byte_order(stream);
   else
      status = read_byte_order(stream, &is_native_order);
   if (status != VC_CONTAINER_SUCCESS) goto error;

   module = malloc( sizeof(*module) );
   if(!module) { status = VC_CONTAINER_ERROR_OUT_OF_MEMORY; goto error; }
   memset(module, 0, sizeof(*module));

   p_ctx->module = module;
   module->stream = stream;
   module->is_native_order = is_native_order;
   p_ctx->pf_close = io_pktfile_close;
   p_ctx->pf_read = io_pktfile_read;
   p_ctx->pf_write = io_pktfile_write;

   /* Do not allow caching by I/O core, as this will merge packets in the cache. */
   p_ctx->capabilities = VC_CONTAINER_IO_CAPS_CANT_SEEK;
   return VC_CONTAINER_SUCCESS;

error:
   if(stream) fclose(stream);
   return status;
}