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
struct TYPE_4__ {struct TYPE_4__* Buf; } ;
typedef  TYPE_1__ BUF ;

/* Variables and functions */
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  KS_CURRENT_BUF_COUNT ; 
 int /*<<< orphan*/  KS_DEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_FREEBUF_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 

void FreeBuf(BUF *b)
{
	// Validate arguments
	if (b == NULL)
	{
		return;
	}

	// Memory release
	Free(b->Buf);
	Free(b);

	// KS
	KS_INC(KS_FREEBUF_COUNT);
	KS_DEC(KS_CURRENT_BUF_COUNT);
}