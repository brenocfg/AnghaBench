#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  Size; int /*<<< orphan*/  Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 TYPE_1__* MemToBuf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

BUF *CloneBuf(BUF *b)
{
	BUF *bb;
	// Validate arguments
	if (b == NULL)
	{
		return NULL;
	}

	bb = MemToBuf(b->Buf, b->Size);

	return bb;
}