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
typedef  int /*<<< orphan*/  kmutex_t ;
typedef  int /*<<< orphan*/  kcondvar_t ;

/* Variables and functions */
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
cv_wait_sig(kcondvar_t *cv, kmutex_t *mp)
{
	cv_wait(cv, mp);
	return (0);
}