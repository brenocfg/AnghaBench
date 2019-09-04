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
typedef  int /*<<< orphan*/  vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ pc_buffer ; 
 scalar_t__ pc_bufsize ; 
 scalar_t__ pcsample_enable ; 
 int pcsamples_bootstrap () ; 

int
pcsamples_reinit(void)
{
    int ret=0;

    pcsample_enable = 0;

	if (pc_bufsize && pc_buffer)
		kmem_free(kernel_map, (vm_offset_t)pc_buffer, pc_bufsize);

	ret= pcsamples_bootstrap();
	return(ret);
}