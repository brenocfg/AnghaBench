#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  upl_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  upl_abort (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  upl_deallocate (int /*<<< orphan*/ ) ; 

kern_return_t
ubc_upl_abort(
	upl_t			upl,
	int				abort_type)
{
	kern_return_t	kr;

	kr = upl_abort(upl, abort_type);
	upl_deallocate(upl);
	return kr;
}