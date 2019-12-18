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
struct TYPE_4__ {scalar_t__ Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 scalar_t__ Cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

bool CompareBuf(BUF *b1, BUF *b2)
{
	// Validate arguments
	if (b1 == NULL && b2 == NULL)
	{
		return true;
	}
	if (b1 == NULL || b2 == NULL)
	{
		return false;
	}

	if (b1->Size != b2->Size)
	{
		return false;
	}

	if (Cmp(b1->Buf, b2->Buf, b1->Size) != 0)
	{
		return false;
	}

	return true;
}