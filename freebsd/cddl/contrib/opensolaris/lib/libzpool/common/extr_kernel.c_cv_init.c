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
typedef  int /*<<< orphan*/  kcondvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int) ; 
 scalar_t__ cond_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 

void
cv_init(kcondvar_t *cv, char *name, int type, void *arg)
{
	VERIFY(cond_init(cv, name, NULL) == 0);
}