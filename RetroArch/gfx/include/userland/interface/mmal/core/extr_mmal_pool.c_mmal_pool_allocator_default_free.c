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

/* Variables and functions */
 int /*<<< orphan*/  MMAL_PARAM_UNUSED (void*) ; 
 int /*<<< orphan*/  vcos_free (void*) ; 

__attribute__((used)) static void mmal_pool_allocator_default_free(void *context, void *mem)
{
   MMAL_PARAM_UNUSED(context);
   vcos_free(mem);
}