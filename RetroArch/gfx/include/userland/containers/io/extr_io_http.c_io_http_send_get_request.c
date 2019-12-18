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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_5__ {scalar_t__ size; int /*<<< orphan*/  uri_parts; TYPE_2__* module; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
struct TYPE_6__ {char* comms_buffer; scalar_t__ cur_offset; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_MODULE_T ;

/* Variables and functions */
 scalar_t__ ENABLE_HTTP_EXTRA_LOGGING ; 
 int /*<<< orphan*/  GET_METHOD ; 
 char* HTTP_RANGE_REQUEST ; 
 char* HTTP_REQUEST_LINE_FORMAT ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  LOG_ERROR (int /*<<< orphan*/ ,char*,int,int) ; 
 char* TRAILING_HEADERS_FORMAT ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_RESOURCES ; 
 int /*<<< orphan*/  io_http_send (TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  vc_uri_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_path (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T io_http_send_get_request(VC_CONTAINER_IO_T *p_ctx, size_t size)
{
   VC_CONTAINER_IO_MODULE_T *module = p_ctx->module;
   char *ptr = module->comms_buffer, *end = ptr + sizeof(module->comms_buffer);
   int64_t end_offset;

   ptr += snprintf(ptr, end - ptr, HTTP_REQUEST_LINE_FORMAT, GET_METHOD,
                   vc_uri_path(p_ctx->uri_parts), vc_uri_host(p_ctx->uri_parts));

   end_offset = module->cur_offset + size - 1;
   if (end_offset >= p_ctx->size)
      end_offset = p_ctx->size - 1;

   if (ptr < end)
      ptr += snprintf(ptr, end - ptr, HTTP_RANGE_REQUEST, module->cur_offset, end_offset);

   if (ptr < end)
      ptr += snprintf(ptr, end - ptr, TRAILING_HEADERS_FORMAT);

   if (ptr >= end)
   {
      LOG_ERROR(0, "comms buffer too small (%i/%u)", (int)(end - ptr),
                sizeof(module->comms_buffer));
      return VC_CONTAINER_ERROR_OUT_OF_RESOURCES;
   }

   if (ENABLE_HTTP_EXTRA_LOGGING)
      LOG_DEBUG(NULL, "Sending server read request:\n%s\n---------------------\n", module->comms_buffer);
   return io_http_send(p_ctx);
}