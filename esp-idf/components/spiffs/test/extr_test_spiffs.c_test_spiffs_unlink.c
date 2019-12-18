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
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_NULL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fopen (char const*,char*) ; 
 int /*<<< orphan*/  test_spiffs_create_file_with_text (char const*,char*) ; 
 int /*<<< orphan*/  unlink (char const*) ; 

void test_spiffs_unlink(const char* filename)
{
    test_spiffs_create_file_with_text(filename, "unlink\n");

    TEST_ASSERT_EQUAL(0, unlink(filename));

    TEST_ASSERT_NULL(fopen(filename, "r"));
}