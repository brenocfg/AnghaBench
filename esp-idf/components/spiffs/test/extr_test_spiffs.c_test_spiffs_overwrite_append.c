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
 int /*<<< orphan*/  EOF ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_STRING_LEN (char*,char*,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_spiffs_create_file_with_text (char const*,char*) ; 

void test_spiffs_overwrite_append(const char* filename)
{
    /* Create new file with 'aaaa' */
    test_spiffs_create_file_with_text(filename, "aaaa");

    /* Append 'bbbb' to file */
    FILE *f_a = fopen(filename, "a");
    TEST_ASSERT_NOT_NULL(f_a);
    TEST_ASSERT_NOT_EQUAL(EOF, fputs("bbbb", f_a));
    TEST_ASSERT_EQUAL(0, fclose(f_a));

    /* Read back 8 bytes from file, verify it's 'aaaabbbb' */
    char buf[10] = { 0 };
    FILE *f_r = fopen(filename, "r");
    TEST_ASSERT_NOT_NULL(f_r);
    TEST_ASSERT_EQUAL(8, fread(buf, 1, 8, f_r));
    TEST_ASSERT_EQUAL_STRING_LEN("aaaabbbb", buf, 8);

    /* Be sure we're at end of file */
    TEST_ASSERT_EQUAL(0, fread(buf, 1, 8, f_r));

    TEST_ASSERT_EQUAL(0, fclose(f_r));

    /* Overwrite file with 'cccc' */
    test_spiffs_create_file_with_text(filename, "cccc");

    /* Verify file now only contains 'cccc' */
    f_r = fopen(filename, "r");
    TEST_ASSERT_NOT_NULL(f_r);
    bzero(buf, sizeof(buf));
    TEST_ASSERT_EQUAL(4, fread(buf, 1, 8, f_r)); // trying to read 8 bytes, only expecting 4
    TEST_ASSERT_EQUAL_STRING_LEN("cccc", buf, 4);
    TEST_ASSERT_EQUAL(0, fclose(f_r));
}