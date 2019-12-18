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
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 

void
atf_require_inside_if(void)
{
    /* Make sure that ATF_REQUIRE can be used inside an if statement that
     * does not have braces.  Earlier versions of it generated an error
     * if there was an else clause because they confused the compiler
     * by defining an unprotected nested if. */
    if (true)
        ATF_REQUIRE(true);
    else
        ATF_REQUIRE(true);
}