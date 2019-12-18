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
 int /*<<< orphan*/  free_pages_exact (void*,size_t) ; 
 int /*<<< orphan*/  pr_debug (char*,void*,size_t) ; 

__attribute__((used)) static void fsl_diu_free(void *virt, size_t size)
{
	pr_debug("virt=%p size=%zu\n", virt, size);

	if (virt && size)
		free_pages_exact(virt, size);
}