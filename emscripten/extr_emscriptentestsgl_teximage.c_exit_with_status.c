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
typedef  int /*<<< orphan*/  TestStatus ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void exit_with_status(TestStatus code)
{
#ifdef REPORT_RESULT
    int result = (code == TEST_STATUS_SUCCESS) ? 1 : 0;
    REPORT_RESULT(result);
#endif

    exit(code);
}