#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT64 ;
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {scalar_t__ size; int pos; int fixed; int /*<<< orphan*/  total_read_size; scalar_t__ p; } ;
typedef  TYPE_1__ FIFO ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_READ_FIFO_COUNT ; 
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ShrinkFifoMemory (TYPE_1__*) ; 

UINT ReadFifo(FIFO *f, void *p, UINT size)
{
	UINT read_size;
	// Validate arguments
	if (f == NULL || size == 0)
	{
		return 0;
	}

	read_size = MIN(size, f->size);
	if (read_size == 0)
	{
		return 0;
	}
	if (p != NULL)
	{
		Copy(p, (UCHAR *)f->p + f->pos, read_size);
	}
	f->pos += read_size;
	f->size -= read_size;

	f->total_read_size += (UINT64)read_size;

	if (f->fixed == false)
	{
		if (f->size == 0)
		{
			f->pos = 0;
		}
	}

	ShrinkFifoMemory(f);

	// KS
	KS_INC(KS_READ_FIFO_COUNT);

	return read_size;
}