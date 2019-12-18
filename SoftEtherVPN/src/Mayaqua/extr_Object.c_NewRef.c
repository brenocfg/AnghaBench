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
struct TYPE_4__ {int /*<<< orphan*/  c; } ;
typedef  TYPE_1__ REF ;

/* Variables and functions */
 int /*<<< orphan*/  Inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_ADDREF_COUNT ; 
 int /*<<< orphan*/  KS_CURRENT_REFED_COUNT ; 
 int /*<<< orphan*/  KS_CURRENT_REF_COUNT ; 
 int /*<<< orphan*/  KS_INC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KS_NEWREF_COUNT ; 
 TYPE_1__* Malloc (int) ; 
 int /*<<< orphan*/  NewCounter () ; 

REF *NewRef()
{
	REF *ref;

	// Memory allocation
	ref = Malloc(sizeof(REF));

	// Create a Counter
	ref->c = NewCounter();

	// Increment only once
	Inc(ref->c);

	// KS
	KS_INC(KS_NEWREF_COUNT);
	KS_INC(KS_CURRENT_REF_COUNT);
	KS_INC(KS_ADDREF_COUNT);
	KS_INC(KS_CURRENT_REFED_COUNT);

	return ref;
}