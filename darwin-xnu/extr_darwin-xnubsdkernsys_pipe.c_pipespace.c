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
typedef  scalar_t__ vm_offset_t ;
struct TYPE_2__ {int size; scalar_t__ cnt; scalar_t__ out; scalar_t__ in; scalar_t__ buffer; } ;
struct pipe {TYPE_1__ pipe_buffer; } ;
typedef  scalar_t__ caddr_t ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  OSAddAtomic (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  amountpipekva ; 
 int /*<<< orphan*/  amountpipes ; 
 scalar_t__ kalloc (int) ; 
 int /*<<< orphan*/  pipe_free_kmem (struct pipe*) ; 

__attribute__((used)) static int
pipespace(struct pipe *cpipe, int size)
{
	vm_offset_t buffer;

	if (size <= 0)
		return(EINVAL);

	if ((buffer = (vm_offset_t)kalloc(size)) == 0 )
		return(ENOMEM);

	/* free old resources if we're resizing */
	pipe_free_kmem(cpipe);
	cpipe->pipe_buffer.buffer = (caddr_t)buffer;
	cpipe->pipe_buffer.size = size;
	cpipe->pipe_buffer.in = 0;
	cpipe->pipe_buffer.out = 0;
	cpipe->pipe_buffer.cnt = 0;

	OSAddAtomic(1, &amountpipes);
	OSAddAtomic(cpipe->pipe_buffer.size, &amountpipekva);

	return (0);
}