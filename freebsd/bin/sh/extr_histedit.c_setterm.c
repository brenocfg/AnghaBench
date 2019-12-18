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

/* Variables and functions */
 int /*<<< orphan*/  EL_TERMINAL ; 
 int /*<<< orphan*/ * el ; 
 int /*<<< orphan*/  el_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ rootshell ; 

void
setterm(const char *term)
{
	if (rootshell && el != NULL && term != NULL)
		el_set(el, EL_TERMINAL, term);
}