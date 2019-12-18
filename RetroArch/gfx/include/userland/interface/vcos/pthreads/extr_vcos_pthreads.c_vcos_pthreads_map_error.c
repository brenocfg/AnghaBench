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
typedef  int /*<<< orphan*/  VCOS_STATUS_T ;

/* Variables and functions */
#define  EAGAIN 131 
#define  ENOMEM 130 
#define  ENOSPC 129 
#define  ENXIO 128 
 int /*<<< orphan*/  VCOS_EAGAIN ; 
 int /*<<< orphan*/  VCOS_EINVAL ; 
 int /*<<< orphan*/  VCOS_ENOMEM ; 
 int /*<<< orphan*/  VCOS_ENOSPC ; 
 int /*<<< orphan*/  VCOS_ENXIO ; 

VCOS_STATUS_T vcos_pthreads_map_error(int error)
{
   switch (error)
   {
   case ENOMEM:
      return VCOS_ENOMEM;
   case ENXIO:
      return VCOS_ENXIO;
   case EAGAIN:
      return VCOS_EAGAIN;
   case ENOSPC:
      return VCOS_ENOSPC;
   default:
      return VCOS_EINVAL;
   }
}