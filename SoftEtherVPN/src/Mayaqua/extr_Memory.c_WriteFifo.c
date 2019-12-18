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
typedef  scalar_t__ UINT64 ;
typedef  int UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_3__ {int size; int pos; int memsize; int /*<<< orphan*/  total_write_size; scalar_t__ p; } ;
typedef  TYPE_1__ FIFO ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  FIFO_INIT_MEM_SIZE ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_WRITE_FIFO_COUNT ; 
 int MAX (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ReAlloc (scalar_t__,int) ; 

void WriteFifo(FIFO *f, void *p, UINT size)
{
	UINT i, need_size;
	bool realloc_flag;
	// Validate arguments
	if (f == NULL || size == 0)
	{
		return;
	}

	i = f->size;
	f->size += size;
	need_size = f->pos + f->size;
	realloc_flag = false;

	// Memory expansion
	while (need_size > f->memsize)
	{
		f->memsize = MAX(f->memsize, FIFO_INIT_MEM_SIZE) * 3;
		realloc_flag = true;
	}

	if (realloc_flag)
	{
		f->p = ReAlloc(f->p, f->memsize);
	}

	// Write the data
	if (p != NULL)
	{
		Copy((UCHAR *)f->p + f->pos + i, p, size);
	}

	f->total_write_size += (UINT64)size;

	// KS
	KS_INC(KS_WRITE_FIFO_COUNT);
}