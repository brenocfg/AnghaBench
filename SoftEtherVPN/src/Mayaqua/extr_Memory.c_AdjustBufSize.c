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
struct TYPE_3__ {int SizeReserved; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  KS_ADJUST_BUFSIZE_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReAlloc (int /*<<< orphan*/ ,int) ; 

void AdjustBufSize(BUF *b, UINT new_size)
{
	// Validate arguments
	if (b == NULL)
	{
		return;
	}

	if (b->SizeReserved >= new_size)
	{
		return;
	}

	while (b->SizeReserved < new_size)
	{
		b->SizeReserved = b->SizeReserved * 2;
	}
	b->Buf = ReAlloc(b->Buf, b->SizeReserved);

	// KS
	KS_INC(KS_ADJUST_BUFSIZE_COUNT);
}