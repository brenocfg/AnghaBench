#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int vc_container_net_status_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_ABORTED ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CONTINUE ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_EOS ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FAILED ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_NOT_FOUND ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_URI_OPEN_FAILED ; 
#define  VC_CONTAINER_NET_ERROR_CONNECTION_LOST 140 
#define  VC_CONTAINER_NET_ERROR_CONNECTION_REFUSED 139 
#define  VC_CONTAINER_NET_ERROR_HOST_NOT_FOUND 138 
#define  VC_CONTAINER_NET_ERROR_INVALID_PARAMETER 137 
#define  VC_CONTAINER_NET_ERROR_INVALID_SOCKET 136 
#define  VC_CONTAINER_NET_ERROR_IN_USE 135 
#define  VC_CONTAINER_NET_ERROR_NETWORK 134 
#define  VC_CONTAINER_NET_ERROR_NOT_ALLOWED 133 
#define  VC_CONTAINER_NET_ERROR_NOT_CONNECTED 132 
#define  VC_CONTAINER_NET_ERROR_NO_MEMORY 131 
#define  VC_CONTAINER_NET_ERROR_TIMED_OUT 130 
#define  VC_CONTAINER_NET_ERROR_TRY_AGAIN 129 
#define  VC_CONTAINER_NET_SUCCESS 128 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T translate_net_status_to_container_status(vc_container_net_status_t net_status)
{
   switch (net_status)
   {
   case VC_CONTAINER_NET_SUCCESS:                  return VC_CONTAINER_SUCCESS;
   case VC_CONTAINER_NET_ERROR_INVALID_SOCKET:     return VC_CONTAINER_ERROR_INVALID_ARGUMENT;
   case VC_CONTAINER_NET_ERROR_NOT_ALLOWED:        return VC_CONTAINER_ERROR_UNSUPPORTED_OPERATION;
   case VC_CONTAINER_NET_ERROR_INVALID_PARAMETER:  return VC_CONTAINER_ERROR_INVALID_ARGUMENT;
   case VC_CONTAINER_NET_ERROR_NO_MEMORY:          return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
   case VC_CONTAINER_NET_ERROR_IN_USE:             return VC_CONTAINER_ERROR_URI_OPEN_FAILED;
   case VC_CONTAINER_NET_ERROR_NETWORK:            return VC_CONTAINER_ERROR_EOS;
   case VC_CONTAINER_NET_ERROR_CONNECTION_LOST:    return VC_CONTAINER_ERROR_EOS;
   case VC_CONTAINER_NET_ERROR_NOT_CONNECTED:      return VC_CONTAINER_ERROR_INVALID_ARGUMENT;
   case VC_CONTAINER_NET_ERROR_TIMED_OUT:          return VC_CONTAINER_ERROR_ABORTED;
   case VC_CONTAINER_NET_ERROR_CONNECTION_REFUSED: return VC_CONTAINER_ERROR_NOT_FOUND;
   case VC_CONTAINER_NET_ERROR_HOST_NOT_FOUND:     return VC_CONTAINER_ERROR_NOT_FOUND;
   case VC_CONTAINER_NET_ERROR_TRY_AGAIN:          return VC_CONTAINER_ERROR_CONTINUE;
   default:                                        return VC_CONTAINER_ERROR_FAILED;
   }
}