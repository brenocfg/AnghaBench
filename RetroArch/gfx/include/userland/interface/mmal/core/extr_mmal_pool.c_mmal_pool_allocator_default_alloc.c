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

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (void*) ; 
 void* vcos_malloc (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void *mmal_pool_allocator_default_alloc(void *context, uint32_t size)
{
   MMAL_PARAM_UNUSED(context);
   return vcos_malloc(size, "mmal_pool payload");
}