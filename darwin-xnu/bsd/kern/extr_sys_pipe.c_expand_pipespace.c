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
struct TYPE_2__ {unsigned int size; scalar_t__ cnt; scalar_t__ in; scalar_t__ out; int /*<<< orphan*/ * buffer; } ;
struct pipe {TYPE_1__ pipe_buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  pipe_free_kmem (struct pipe*) ; 
 int pipespace (struct pipe*,int) ; 

__attribute__((used)) static int 
expand_pipespace(struct pipe *p, int target_size)
{
	struct pipe tmp, oldpipe;
	int error;
	tmp.pipe_buffer.buffer = 0;
	
	if (p->pipe_buffer.size >= (unsigned) target_size) {
		return 0; /* the existing buffer is max size possible */
	}
	
	/* create enough space in the target */
	error = pipespace(&tmp, target_size);
	if (error != 0)
		return (error);

	oldpipe.pipe_buffer.buffer = p->pipe_buffer.buffer;
	oldpipe.pipe_buffer.size = p->pipe_buffer.size;
	
	memcpy(tmp.pipe_buffer.buffer, p->pipe_buffer.buffer, p->pipe_buffer.size);
	if (p->pipe_buffer.cnt > 0 && p->pipe_buffer.in <= p->pipe_buffer.out ){
		/* we are in State 3 and need extra copying for read to be consistent */
		memcpy(&tmp.pipe_buffer.buffer[p->pipe_buffer.size], p->pipe_buffer.buffer, p->pipe_buffer.size);
		p->pipe_buffer.in += p->pipe_buffer.size;
	}

	p->pipe_buffer.buffer = tmp.pipe_buffer.buffer;
	p->pipe_buffer.size = tmp.pipe_buffer.size;


	pipe_free_kmem(&oldpipe);
	return 0;
}