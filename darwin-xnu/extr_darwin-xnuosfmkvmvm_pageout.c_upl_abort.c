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
typedef  TYPE_1__* upl_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_5__ {int /*<<< orphan*/  size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 TYPE_1__* UPL_NULL ; 
 int /*<<< orphan*/  upl_abort_range (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

kern_return_t
upl_abort(
	upl_t	upl,
	int	error)
{
	boolean_t	empty;

	if (upl == UPL_NULL)
		return KERN_INVALID_ARGUMENT;

	return upl_abort_range(upl, 0, upl->size, error, &empty);
}