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
typedef  int /*<<< orphan*/  vc_container_net_status_t ;
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
struct TYPE_5__ {scalar_t__ socket; int /*<<< orphan*/  status; int /*<<< orphan*/  to_addr_len; TYPE_1__ to_addr; } ;
typedef  TYPE_2__ VC_CONTAINER_NET_T ;

/* Variables and functions */
 scalar_t__ INVALID_SOCKET ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_SOCKET ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NOT_CONNECTED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_SUCCESS ; 
 int getnameinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  translate_getnameinfo_error (int) ; 

vc_container_net_status_t vc_container_net_get_client_name( VC_CONTAINER_NET_T *p_ctx, char *name, size_t name_len )
{
   int result;

   if (!p_ctx)
      return VC_CONTAINER_NET_ERROR_INVALID_SOCKET;

   if (p_ctx->socket == INVALID_SOCKET)
      p_ctx->status = VC_CONTAINER_NET_ERROR_NOT_CONNECTED;
   else if (!name || !name_len)
      p_ctx->status = VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
   else if ((result = getnameinfo(&p_ctx->to_addr.sa, p_ctx->to_addr_len, name, name_len, NULL, 0, 0)) != 0)
      p_ctx->status = translate_getnameinfo_error(result);
   else
      p_ctx->status = VC_CONTAINER_NET_SUCCESS;

   return p_ctx->status;
}