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
 int /*<<< orphan*/  protocomm_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * test_pc ; 
 int /*<<< orphan*/ * test_sec ; 

__attribute__((used)) static void stop_test_service(void)
{
    test_sec = NULL;
    protocomm_delete(test_pc);
    test_pc = NULL;
}