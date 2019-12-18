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
typedef  int /*<<< orphan*/ * vector_upl_t ;
typedef  TYPE_1__* upl_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int flags; int /*<<< orphan*/ * vector_upl; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int UPL_VECTOR ; 

boolean_t
vector_upl_is_valid(upl_t upl)
{
	if(upl &&  ((upl->flags & UPL_VECTOR)==UPL_VECTOR)) {
		vector_upl_t vector_upl = upl->vector_upl;
		if(vector_upl == NULL || vector_upl == (vector_upl_t)0xfeedfeed || vector_upl == (vector_upl_t)0xfeedbeef)
			return FALSE;
		else
			return TRUE;
	}
	return FALSE;
}