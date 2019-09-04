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
typedef  scalar_t__ UINT ;
struct TYPE_4__ {scalar_t__ c; } ;
typedef  TYPE_1__ REF ;

/* Variables and functions */
 scalar_t__ Dec (scalar_t__) ; 
 int /*<<< orphan*/  DeleteCounter (scalar_t__) ; 
 int /*<<< orphan*/  Free (TYPE_1__*) ; 
 int /*<<< orphan*/  KS_CURRENT_REFED_COUNT ; 
 int /*<<< orphan*/  KS_CURRENT_REF_COUNT ; 
 int /*<<< orphan*/  KS_DEC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_FREEREF_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_RELEASE_COUNT ; 

UINT Release(REF *ref)
{
	UINT c;
	// Validate arguments
	if (ref == NULL)
	{
		return 0;
	}

	// KS
	KS_INC(KS_RELEASE_COUNT);
	KS_DEC(KS_CURRENT_REFED_COUNT);

	c = Dec(ref->c);
	if (c == 0)
	{
		// KS
		KS_DEC(KS_CURRENT_REF_COUNT);
		KS_INC(KS_FREEREF_COUNT);

		DeleteCounter(ref->c);
		ref->c = 0;
		Free(ref);
	}
	return c;
}