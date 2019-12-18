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
struct uthread {scalar_t__ pth_name; } ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

boolean_t
bsd_hasthreadname(void *uth)
{
	struct uthread *ut = (struct uthread*)uth;

	/* This doesn't check for the empty string; do we care? */
	if (ut->pth_name) {
		return TRUE;
	} else {
		return FALSE;
	}
}