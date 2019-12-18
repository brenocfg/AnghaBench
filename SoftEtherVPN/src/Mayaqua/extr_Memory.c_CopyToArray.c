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
struct TYPE_3__ {int num_item; int /*<<< orphan*/  p; } ;
typedef  TYPE_1__ LIST ;

/* Variables and functions */
 int /*<<< orphan*/  Copy (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_TOARRAY_COUNT ; 

void CopyToArray(LIST *o, void *p)
{
	// Validate arguments
	if (o == NULL || p == NULL)
	{
		return;
	}

	// KS
	KS_INC(KS_TOARRAY_COUNT);

	Copy(p, o->p, sizeof(void *) * o->num_item);
}