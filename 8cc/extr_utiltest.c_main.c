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
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  test_buf () ; 
 int /*<<< orphan*/  test_dict () ; 
 int /*<<< orphan*/  test_file () ; 
 int /*<<< orphan*/  test_list () ; 
 int /*<<< orphan*/  test_map () ; 
 int /*<<< orphan*/  test_map_stack () ; 
 int /*<<< orphan*/  test_path () ; 
 int /*<<< orphan*/  test_set () ; 

int main(int argc, char **argv) {
    test_buf();
    test_list();
    test_map();
    test_map_stack();
    test_dict();
    test_set();
    test_path();
    test_file();
    printf("Passed\n");
    return 0;
}