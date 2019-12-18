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
typedef  int /*<<< orphan*/  vm_size_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOTSUP ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  disable_branch_tracing () ; 
 int /*<<< orphan*/  kernel_map ; 
 scalar_t__ kmem_alloc (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int npcbufs ; 
 unsigned int* pc_buffer ; 
 unsigned int* pc_buflast ; 
 unsigned int* pc_bufptr ; 
 int pc_bufsize ; 
 scalar_t__ pc_buftomem ; 
 scalar_t__ pcsample_enable ; 

int
pcsamples_bootstrap(void)
{
        if (!disable_branch_tracing())
            return(ENOTSUP);

	pc_bufsize = npcbufs * sizeof(* pc_buffer);
	if (kmem_alloc(kernel_map, &pc_buftomem,
		       (vm_size_t)pc_bufsize) == KERN_SUCCESS) 
	  pc_buffer = (unsigned int *) pc_buftomem;
	else 
	  pc_buffer = NULL;

	if (pc_buffer) {
		pc_bufptr = pc_buffer;
		pc_buflast = &pc_bufptr[npcbufs];
		pcsample_enable = 0;
		return(0);
	} else {
		pc_bufsize=0;
		return(EINVAL);
	}
	
}