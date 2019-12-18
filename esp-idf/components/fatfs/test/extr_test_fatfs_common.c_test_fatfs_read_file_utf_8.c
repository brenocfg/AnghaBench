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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatfs_test_hello_str_utf ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

void test_fatfs_read_file_utf_8(const char* filename)
{
    FILE* f = fopen(filename, "r");
    TEST_ASSERT_NOT_NULL(f);
    char buf[64] = { 0 };   //Doubled buffer size to allow for longer UTF-8 strings
    int cb = fread(buf, 1, sizeof(buf), f);
    TEST_ASSERT_EQUAL(strlen(fatfs_test_hello_str_utf), cb);
    TEST_ASSERT_EQUAL(0, strcmp(fatfs_test_hello_str_utf, buf));
    TEST_ASSERT_EQUAL(0, fclose(f));
}