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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  VC_CONTAINER_IO_T ;

/* Variables and functions */
 int INITIAL_READ_BUFFER_SIZE ; 
 int MAXIMUM_READ_BUFFER_SIZE ; 
 int /*<<< orphan*/  VC_CONTAINER_CONTROL_IO_SET_READ_BUFFER_SIZE ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ vc_container_io_control (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void increase_read_buffer_size(VC_CONTAINER_IO_T *p_ctx)
{
   uint32_t buffer_size = INITIAL_READ_BUFFER_SIZE;

   /* Iteratively enlarge read buffer until either operation fails or maximum is reached. */
   while (vc_container_io_control(p_ctx, VC_CONTAINER_CONTROL_IO_SET_READ_BUFFER_SIZE, buffer_size) == VC_CONTAINER_SUCCESS)
   {
      buffer_size <<= 1;   /* Double and try again */
      if (buffer_size > MAXIMUM_READ_BUFFER_SIZE)
         break;
   }
}