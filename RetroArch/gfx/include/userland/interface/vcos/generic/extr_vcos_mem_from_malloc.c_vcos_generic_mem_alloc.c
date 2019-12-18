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
typedef  int /*<<< orphan*/  VCOS_UNSIGNED ;

/* Variables and functions */
 int /*<<< orphan*/  MIN_ALIGN ; 
 void* vcos_generic_mem_alloc_aligned (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 

void *vcos_generic_mem_alloc(VCOS_UNSIGNED size, const char *desc)
{
   return vcos_generic_mem_alloc_aligned(size,MIN_ALIGN,desc);
}