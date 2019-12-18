#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {scalar_t__ pos; int memsize; int size; void* p; scalar_t__ fixed; } ;
typedef  TYPE_1__ FIFO ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ FIFO_INIT_MEM_SIZE ; 
 int /*<<< orphan*/  Free (void*) ; 
 int MAX (int,scalar_t__) ; 
 void* Malloc (int) ; 
 int fifo_current_realloc_mem_size ; 

void ShrinkFifoMemory(FIFO *f)
{
	// Validate arguments
	if (f == NULL)
	{
		return;
	}

	if (f->fixed)
	{
		return;
	}

	// Rearrange the memory
	if (f->pos >= FIFO_INIT_MEM_SIZE && 
		f->memsize >= fifo_current_realloc_mem_size &&
		(f->memsize / 2) > f->size)
	{
		void *new_p;
		UINT new_size;

		new_size = MAX(f->memsize / 2, FIFO_INIT_MEM_SIZE);
		new_p = Malloc(new_size);
		Copy(new_p, (UCHAR *)f->p + f->pos, f->size);

		Free(f->p);

		f->memsize = new_size;
		f->p = new_p;
		f->pos = 0;
	}
}