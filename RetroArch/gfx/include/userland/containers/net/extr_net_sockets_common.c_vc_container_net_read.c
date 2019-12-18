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
struct TYPE_5__ {int /*<<< orphan*/  sa; } ;
struct TYPE_6__ {int type; void* status; int /*<<< orphan*/  to_addr_len; TYPE_1__ to_addr; int /*<<< orphan*/  socket; int /*<<< orphan*/  read_timeout_ms; } ;
typedef  TYPE_2__ VC_CONTAINER_NET_T ;

/* Variables and functions */
#define  DATAGRAM_RECEIVER 130 
 int SOCKET_ERROR ; 
#define  STREAM_CLIENT 129 
#define  STREAM_SERVER 128 
 void* VC_CONTAINER_NET_ERROR_CONNECTION_LOST ; 
 void* VC_CONTAINER_NET_ERROR_INVALID_PARAMETER ; 
 void* VC_CONTAINER_NET_ERROR_NOT_ALLOWED ; 
 void* VC_CONTAINER_NET_ERROR_TIMED_OUT ; 
 void* VC_CONTAINER_NET_SUCCESS ; 
 int recv (int /*<<< orphan*/ ,void*,int,int /*<<< orphan*/ ) ; 
 int recvfrom (int /*<<< orphan*/ ,void*,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  socket_wait_for_data (TYPE_2__*,int /*<<< orphan*/ ) ; 
 void* vc_container_net_private_last_error () ; 

size_t vc_container_net_read( VC_CONTAINER_NET_T *p_ctx, void *buffer, size_t size )
{
   int result = 0;

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
      /* Receive data from the stream */
      if (socket_wait_for_data(p_ctx, p_ctx->read_timeout_ms))
      {
         result = recv(p_ctx->socket, buffer, (int)size, 0);
         if (!result)
            p_ctx->status = VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
      } else
         p_ctx->status = VC_CONTAINER_NET_ERROR_TIMED_OUT;
      break;

   case DATAGRAM_RECEIVER:
      {
         /* Receive the packet */
         /* FIXME Potential for data loss, as rest of packet will be lost if buffer was not large enough */
         if (socket_wait_for_data(p_ctx, p_ctx->read_timeout_ms))
         {
            result = recvfrom(p_ctx->socket, buffer, size, 0, &p_ctx->to_addr.sa, &p_ctx->to_addr_len);
            if (!result)
               p_ctx->status = VC_CONTAINER_NET_ERROR_CONNECTION_LOST;
         } else
            p_ctx->status = VC_CONTAINER_NET_ERROR_TIMED_OUT;
      }
      break;

   default: /* DATAGRAM_SENDER */
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