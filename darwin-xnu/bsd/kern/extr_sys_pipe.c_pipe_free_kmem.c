#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int size; int /*<<< orphan*/ * buffer; } ;
struct pipe {TYPE_1__ pipe_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amountpipekva ; 
 int /*<<< orphan*/  amountpipes ; 
 int /*<<< orphan*/  kfree (void*,int) ; 

__attribute__((used)) static void
pipe_free_kmem(struct pipe *cpipe)
{
	if (cpipe->pipe_buffer.buffer != NULL) {
		OSAddAtomic(-(cpipe->pipe_buffer.size), &amountpipekva);
		OSAddAtomic(-1, &amountpipes);
		kfree((void *)cpipe->pipe_buffer.buffer,
			  cpipe->pipe_buffer.size);
		cpipe->pipe_buffer.buffer = NULL;
		cpipe->pipe_buffer.size = 0;
	}
}