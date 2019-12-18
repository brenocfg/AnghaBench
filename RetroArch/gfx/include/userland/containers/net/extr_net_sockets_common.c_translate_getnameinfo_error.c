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
typedef  int /*<<< orphan*/  vc_container_net_status_t ;

/* Variables and functions */
#define  EAI_AGAIN 131 
#define  EAI_FAIL 130 
#define  EAI_MEMORY 129 
#define  EAI_NONAME 128 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_GENERAL ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_HOST_NOT_FOUND ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_NO_MEMORY ; 
 int /*<<< orphan*/  VC_CONTAINER_NET_ERROR_TRY_AGAIN ; 

__attribute__((used)) static vc_container_net_status_t translate_getnameinfo_error( int error )
{
   switch (error)
   {
   case EAI_AGAIN:   return VC_CONTAINER_NET_ERROR_TRY_AGAIN;
   case EAI_FAIL:    return VC_CONTAINER_NET_ERROR_HOST_NOT_FOUND;
   case EAI_MEMORY:  return VC_CONTAINER_NET_ERROR_NO_MEMORY;
   case EAI_NONAME:  return VC_CONTAINER_NET_ERROR_HOST_NOT_FOUND;

   /* All other errors are unexpected, so just map to a general purpose error code. */
   default:
      return VC_CONTAINER_NET_ERROR_GENERAL;
   }
}