#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_3__ {int /*<<< orphan*/  pf_seek; int /*<<< orphan*/  pf_write; int /*<<< orphan*/  pf_read; int /*<<< orphan*/  pf_close; int /*<<< orphan*/  uri_parts; } ;
typedef  TYPE_1__ VC_CONTAINER_IO_T ;
typedef  char const* VC_CONTAINER_IO_MODE_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (char const*) ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  io_null_close ; 
 int /*<<< orphan*/  io_null_read ; 
 int /*<<< orphan*/  io_null_seek ; 
 int /*<<< orphan*/  io_null_write ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  vc_uri_scheme (int /*<<< orphan*/ ) ; 

VC_CONTAINER_STATUS_T vc_container_io_null_open( VC_CONTAINER_IO_T *p_ctx,
   const char *unused, VC_CONTAINER_IO_MODE_T mode )
{
   VC_CONTAINER_PARAM_UNUSED(unused);
   VC_CONTAINER_PARAM_UNUSED(mode);

   /* Check the URI */
   if (!vc_uri_scheme(p_ctx->uri_parts) ||
       (strcasecmp(vc_uri_scheme(p_ctx->uri_parts), "null") &&
        strcasecmp(vc_uri_scheme(p_ctx->uri_parts), "null")))
      return VC_CONTAINER_ERROR_FORMAT_NOT_SUPPORTED;

   p_ctx->pf_close = io_null_close;
   p_ctx->pf_read = io_null_read;
   p_ctx->pf_write = io_null_write;
   p_ctx->pf_seek = io_null_seek;
   return VC_CONTAINER_SUCCESS;
}