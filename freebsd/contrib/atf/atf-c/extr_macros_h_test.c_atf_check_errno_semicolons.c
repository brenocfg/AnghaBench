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
 int /*<<< orphan*/  ATF_CHECK_ERRNO (int,int) ; 

void
atf_check_errno_semicolons(void)
{
    /* Check that ATF_CHECK_ERRNO does not contain a semicolon that would
     * cause an empty-statement that confuses some compilers. */
    ATF_CHECK_ERRNO(1, 1 == 1);
    ATF_CHECK_ERRNO(2, 2 == 2);
}