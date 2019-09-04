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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ REF ;

/* Variables and functions */
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_ADDREF_COUNT ; 
 int /*<<< orphan*/  KS_CURRENT_REFED_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 

UINT AddRef(REF *ref)
{
	UINT c;
	// Validate arguments
	if (ref == NULL)
	{
		return 0;
	}

	c = Inc(ref->c);

	// KS
	KS_INC(KS_ADDREF_COUNT);
	KS_INC(KS_CURRENT_REFED_COUNT);

	return c;
}