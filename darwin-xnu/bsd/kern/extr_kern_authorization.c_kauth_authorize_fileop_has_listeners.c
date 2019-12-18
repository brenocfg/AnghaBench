#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int ks_flags; } ;

/* Variables and functions */
 int KS_F_HAS_LISTENERS ; 
 TYPE_1__* kauth_scope_fileop ; 

int
kauth_authorize_fileop_has_listeners(void)
{
	/*
	 * return 1 if we have any listeners for the fileop scope
	 * otherwize return 0
	 */
	if ((kauth_scope_fileop->ks_flags & KS_F_HAS_LISTENERS) != 0) {
		return(1);
	}
	return (0);
}