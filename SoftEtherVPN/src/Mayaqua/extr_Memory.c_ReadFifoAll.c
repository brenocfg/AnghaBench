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
typedef  int /*<<< orphan*/  UINT ;
typedef  int /*<<< orphan*/  UCHAR ;
typedef  int /*<<< orphan*/  FIFO ;
typedef  int /*<<< orphan*/  BUF ;

/* Variables and functions */
 int /*<<< orphan*/  FifoSize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * MemToBuf (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * NewBuf () ; 
 int /*<<< orphan*/  ReadFifo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

BUF *ReadFifoAll(FIFO *f)
{
	BUF *buf;
	UCHAR *tmp;
	UINT size;
	if (f == NULL)
	{
		return NewBuf();
	}

	size = FifoSize(f);
	tmp = Malloc(size);
	ReadFifo(f, tmp, size);

	buf = MemToBuf(tmp, size);

	Free(tmp);

	return buf;
}