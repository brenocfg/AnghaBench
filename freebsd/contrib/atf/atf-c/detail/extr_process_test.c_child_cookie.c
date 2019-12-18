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
 int /*<<< orphan*/  UNREACHABLE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit_v_notnull ; 
 int /*<<< orphan*/  exit_v_null ; 

__attribute__((used)) static
void
child_cookie(void *v)
{
    if (v == NULL)
        exit(exit_v_null);
    else
        exit(exit_v_notnull);

    UNREACHABLE;
}