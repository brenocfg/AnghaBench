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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  MMAL_POOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_pool_allocator_default_alloc ; 
 int /*<<< orphan*/  mmal_pool_allocator_default_free ; 
 int /*<<< orphan*/ * mmal_pool_create_with_allocator (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

MMAL_POOL_T *mmal_pool_create(unsigned int headers, uint32_t payload_size)
{
   return mmal_pool_create_with_allocator(headers, payload_size, NULL,
             mmal_pool_allocator_default_alloc, mmal_pool_allocator_default_free);
}