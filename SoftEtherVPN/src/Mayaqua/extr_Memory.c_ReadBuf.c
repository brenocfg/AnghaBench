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
typedef  scalar_t__ UINT ;
typedef  void UCHAR ;
struct TYPE_3__ {scalar_t__ Current; scalar_t__ Size; int /*<<< orphan*/ * Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,void*,scalar_t__) ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_READ_BUF_COUNT ; 
 int /*<<< orphan*/  Zero (void*,scalar_t__) ; 

UINT ReadBuf(BUF *b, void *buf, UINT size)
{
	UINT size_read;
	// Validate arguments
	if (b == NULL || size == 0)
	{
		return 0;
	}

	if (b->Buf == NULL)
	{
		Zero(buf, size);
		return 0;
	}
	size_read = size;
	if ((b->Current + size) >= b->Size)
	{
		size_read = b->Size - b->Current;
		if (buf != NULL)
		{
			Zero((UCHAR *)buf + size_read, size - size_read);
		}
	}

	if (buf != NULL)
	{
		Copy(buf, (UCHAR *)b->Buf + b->Current, size_read);
	}

	b->Current += size_read;

	// KS
	KS_INC(KS_READ_BUF_COUNT);

	return size_read;
}