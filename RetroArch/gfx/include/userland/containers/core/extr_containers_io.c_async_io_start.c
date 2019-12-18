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
struct VC_CONTAINER_IO_ASYNC_T {int dummy; } ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_IO_T ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_ERROR_FAILED ; 
 int /*<<< orphan*/  VC_CONTAINER_PARAM_UNUSED (int) ; 

__attribute__((used)) static struct VC_CONTAINER_IO_ASYNC_T *async_io_start( VC_CONTAINER_IO_T *io, int num_areas, VC_CONTAINER_STATUS_T *status )
{
   VC_CONTAINER_PARAM_UNUSED(io);
   VC_CONTAINER_PARAM_UNUSED(num_areas);
   if(status) *status = VC_CONTAINER_ERROR_FAILED;
   return 0;
}