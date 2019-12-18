#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_6__ {TYPE_2__* module; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
struct TYPE_7__ {scalar_t__ header_list; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  io_http_close_socket (TYPE_2__*) ; 
 int /*<<< orphan*/  vc_containers_list_destroy (scalar_t__) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T io_http_close(VC_CONTAINER_IO_T *p_ctx)
{
   VC_CONTAINER_IO_MODULE_T *module = p_ctx->module;

   if (!module)
      return VC_CONTAINER_ERROR_INVALID_ARGUMENT;

   io_http_close_socket(module);
   if (module->header_list)
      vc_containers_list_destroy(module->header_list);

   free(module);
   p_ctx->module = NULL;

   return VC_CONTAINER_SUCCESS;
}