#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_4__ {int /*<<< orphan*/  uri_parts; TYPE_2__* module; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
struct TYPE_5__ {int /*<<< orphan*/  sock; } ;
typedef  TYPE_2__ VC_CONTAINER_IO_MODULE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_URI_NOT_FOUND ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_URI_OPEN_FAILED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_OPEN_FLAG_STREAM ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  vc_container_net_open (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* vc_uri_host (int /*<<< orphan*/ ) ; 
 char* vc_uri_port (int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T io_http_open_socket(VC_CONTAINER_IO_T *ctx)
{
   VC_CONTAINER_IO_MODULE_T *module = ctx->module;
   VC_CONTAINER_STATUS_T status;
   const char *host, *port;

   /* Treat empty host or port strings as not defined */
   port = vc_uri_port(ctx->uri_parts);
   if (port && !*port)
      port = NULL;

   /* Require the port to be defined */
   if (!port)
   {
      status = VC_CONTAINER_ERROR_URI_OPEN_FAILED;
      goto error;
   }

   host = vc_uri_host(ctx->uri_parts);
   if (host && !*host)
      host = NULL;

   if (!host)
   {
      status = VC_CONTAINER_ERROR_URI_OPEN_FAILED;
      goto error;
   }

   module->sock = vc_container_net_open(host, port, VC_CONTAINER_NET_OPEN_FLAG_STREAM, NULL);
   if (!module->sock)
   {
      status = VC_CONTAINER_ERROR_URI_NOT_FOUND;
      goto error;
   }

   return VC_CONTAINER_SUCCESS;

error:
   return status;
}