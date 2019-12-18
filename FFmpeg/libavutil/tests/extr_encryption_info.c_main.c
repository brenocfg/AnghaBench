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
 int /*<<< orphan*/  run_encryption_info_test () ; 
 int /*<<< orphan*/  run_encryption_init_info_test () ; 

int main(int argc, char **argv)
{
    run_encryption_info_test();
    run_encryption_init_info_test();
    return 0;
}