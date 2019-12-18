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
struct TYPE_3__ {int /*<<< orphan*/  pe_scn; } ;
typedef  TYPE_1__ PE ;

/* Variables and functions */
 scalar_t__ STAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_SORT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _PE_Scn ; 
 int /*<<< orphan*/  cmp_scn ; 
 int /*<<< orphan*/  ps_next ; 

__attribute__((used)) static void
sort_sections(PE *pe)
{

	if (STAILQ_EMPTY(&pe->pe_scn))
		return;

	/* Sort the list of Scn by RVA in ascending order. */
	STAILQ_SORT(&pe->pe_scn, _PE_Scn, ps_next, cmp_scn);
}