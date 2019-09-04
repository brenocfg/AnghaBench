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
typedef  int /*<<< orphan*/  fenv_t ;

/* Variables and functions */
 int /*<<< orphan*/  FE_ALL_EXCEPT ; 
 int /*<<< orphan*/  feraiseexcept (int) ; 
 int /*<<< orphan*/  fesetenv (int /*<<< orphan*/  const*) ; 
 int fetestexcept (int /*<<< orphan*/ ) ; 

int feupdateenv(const fenv_t *envp)
{
	int ex = fetestexcept(FE_ALL_EXCEPT);
	fesetenv(envp);
	feraiseexcept(ex);
	return 0;
}