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
struct stat {int st_mode; } ;

/* Variables and functions */
 int S_IFDIR ; 
 int S_IFREG ; 
 int /*<<< orphan*/  TEST_ASSERT (int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_FALSE (int) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 int /*<<< orphan*/  test_spiffs_create_file_with_text (char const*,char*) ; 

void test_spiffs_stat(const char* filename)
{
    test_spiffs_create_file_with_text(filename, "foo\n");
    struct stat st;
    TEST_ASSERT_EQUAL(0, stat(filename, &st));
    TEST_ASSERT(st.st_mode & S_IFREG);
    TEST_ASSERT_FALSE(st.st_mode & S_IFDIR);
}