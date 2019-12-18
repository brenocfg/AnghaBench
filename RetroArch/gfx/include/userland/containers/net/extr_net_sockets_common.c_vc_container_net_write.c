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
struct TYPE_4__ {int /*<<< orphan*/  sa; } ;
struct TYPE_5__ {int type; size_t max_datagram_size; int /*<<< orphan*/  status; int /*<<< orphan*/  to_addr_len; TYPE_1__ to_addr; int /*<<< orphan*/  socket; } ;
typedef  TYPE_2__ VC_CONTAINER_NET_T ;

/* Variables and functions */
#define  DATAGRAM_SENDER 130 
 int SOCKET_ERROR ; 
#define  STREAM_CLIENT 129 
#define  STREAM_SERVER 128 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NOT_ALLOWED ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_SUCCESS ; 
 int send (int /*<<< orphan*/ ,void const*,int,int /*<<< orphan*/ ) ; 
 int sendto (int /*<<< orphan*/ ,void const*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_net_private_last_error () ; 

size_t vc_container_net_write( VC_CONTAINER_NET_T *p_ctx, const void *buffer, size_t size )
{
   int result;

   if (!p_ctx)
      return 0;

   if (!buffer)
   {
      p_ctx->status = VC_CONTAINER_NET_ERROR_INVALID_PARAMETER;
      return 0;
   }

   p_ctx->status = VC_CONTAINER_NET_SUCCESS;

   switch (p_ctx->type)
   {
   case STREAM_CLIENT:
   case STREAM_SERVER:
      /* Send data to the stream */
      result = send(p_ctx->socket, buffer, (int)size, 0);
      break;

   case DATAGRAM_SENDER:
      /* Send the datagram */

      if (size > p_ctx->max_datagram_size)
         size = p_ctx->max_datagram_size;

      result = sendto(p_ctx->socket, buffer, size, 0, &p_ctx->to_addr.sa, p_ctx->to_addr_len);
      break;

   default: /* DATAGRAM_RECEIVER */
      p_ctx->status = VC_CONTAINER_NET_ERROR_NOT_ALLOWED;
      result = 0;
      break;
   }

   if (result == SOCKET_ERROR)
   {
      p_ctx->status = vc_container_net_private_last_error();
      result = 0;
   }

   return (size_t)result;
}