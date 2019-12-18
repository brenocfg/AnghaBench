#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_5__ {scalar_t__ status; TYPE_2__* module; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
struct TYPE_6__ {char* comms_buffer; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_MODULE_T ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 size_t io_http_write (TYPE_1__*,char const*,size_t) ; 
 size_t strlen (char const*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T io_http_send(VC_CONTAINER_IO_T *p_ctx)
{
   VC_CONTAINER_IO_MODULE_T *module = p_ctx->module;
   size_t to_write;
   size_t written;
   const char *buffer = module->comms_buffer;

   to_write = strlen(buffer);

   while (to_write)
   {
      written = io_http_write(p_ctx, buffer, to_write);
      if (p_ctx->status != VC_CONTAINER_SUCCESS)
         break;

      to_write -= written;
      buffer   += written;
   }

   return p_ctx->status;
}