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
typedef  int VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_ECORRUPT ; 
 int /*<<< orphan*/  MMAL_EINVAL ; 
 int /*<<< orphan*/  MMAL_ENOENT ; 
 int /*<<< orphan*/  MMAL_ENOMEM ; 
 int /*<<< orphan*/  MMAL_ENOSPC ; 
 int /*<<< orphan*/  MMAL_ENOTREADY ; 
 int /*<<< orphan*/  MMAL_SUCCESS ; 
#define  VC_CONTAINER_ERROR_CORRUPTED 134 
#define  VC_CONTAINER_ERROR_NOT_FOUND 133 
#define  VC_CONTAINER_ERROR_NOT_READY 132 
#define  VC_CONTAINER_ERROR_OUT_OF_MEMORY 131 
#define  VC_CONTAINER_ERROR_OUT_OF_RESOURCES 130 
#define  VC_CONTAINER_ERROR_URI_NOT_FOUND 129 
#define  VC_CONTAINER_SUCCESS 128 

__attribute__((used)) static MMAL_STATUS_T container_map_to_mmal_status(VC_CONTAINER_STATUS_T cstatus)
{
   switch (cstatus)
   {
      case VC_CONTAINER_SUCCESS: return MMAL_SUCCESS;
      case VC_CONTAINER_ERROR_CORRUPTED: return MMAL_ECORRUPT;
      case VC_CONTAINER_ERROR_OUT_OF_MEMORY: return MMAL_ENOMEM;
      case VC_CONTAINER_ERROR_OUT_OF_RESOURCES: return MMAL_ENOSPC;
      case VC_CONTAINER_ERROR_NOT_READY: return MMAL_ENOTREADY;
      case VC_CONTAINER_ERROR_NOT_FOUND: return MMAL_ENOENT;
      case VC_CONTAINER_ERROR_URI_NOT_FOUND: return MMAL_ENOENT;
      default: return MMAL_EINVAL;
   }
}