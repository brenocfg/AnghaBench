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
typedef  int /*<<< orphan*/  output ;
typedef  int /*<<< orphan*/  input ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_STRING_LEN (char const*,char*,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_NULL (int /*<<< orphan*/ *) ; 
 int errno ; 
 int fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int fprintf (int /*<<< orphan*/ *,char const*) ; 
 int fread (char*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (char const*) ; 
 int truncate (char const*,int) ; 

void test_fatfs_truncate_file(const char* filename)
{
    int read = 0;
    int truncated_len = 0;

    const char input[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char output[sizeof(input)];

    FILE* f = fopen(filename, "wb");

    TEST_ASSERT_NOT_NULL(f);
    TEST_ASSERT_EQUAL(strlen(input), fprintf(f, input));

    TEST_ASSERT_EQUAL(0, fclose(f));


    // Extending file beyond size is not supported
    TEST_ASSERT_EQUAL(-1, truncate(filename, strlen(input) + 1));
    TEST_ASSERT_EQUAL(errno, EPERM);

    TEST_ASSERT_EQUAL(-1, truncate(filename, -1));
    TEST_ASSERT_EQUAL(errno, EPERM);


    // Truncating should succeed
    const char truncated_1[] = "ABCDEFGHIJ";
    truncated_len = strlen(truncated_1);

    TEST_ASSERT_EQUAL(0, truncate(filename, truncated_len));

    f = fopen(filename, "rb");
    TEST_ASSERT_NOT_NULL(f);
    
    memset(output, 0, sizeof(output));
    read = fread(output, 1, sizeof(output), f);
    
    TEST_ASSERT_EQUAL(truncated_len, read);
    TEST_ASSERT_EQUAL_STRING_LEN(truncated_1, output, truncated_len);

    TEST_ASSERT_EQUAL(0, fclose(f));


    // Once truncated, the new file size should be the basis 
    // whether truncation should succeed or not
    TEST_ASSERT_EQUAL(-1, truncate(filename, truncated_len + 1));
    TEST_ASSERT_EQUAL(EPERM, errno);

    TEST_ASSERT_EQUAL(-1, truncate(filename, strlen(input)));
    TEST_ASSERT_EQUAL(EPERM, errno);

    TEST_ASSERT_EQUAL(-1, truncate(filename, strlen(input) + 1));
    TEST_ASSERT_EQUAL(EPERM, errno);

    TEST_ASSERT_EQUAL(-1, truncate(filename, -1));
    TEST_ASSERT_EQUAL(EPERM, errno);


    // Truncating a truncated file should succeed
    const char truncated_2[] = "ABCDE";
    truncated_len = strlen(truncated_2);

    TEST_ASSERT_EQUAL(0, truncate(filename, truncated_len));

    f = fopen(filename, "rb");
    TEST_ASSERT_NOT_NULL(f);
    
    memset(output, 0, sizeof(output));
    read = fread(output, 1, sizeof(output), f);
    
    TEST_ASSERT_EQUAL(truncated_len, read);
    TEST_ASSERT_EQUAL_STRING_LEN(truncated_2, output, truncated_len);

    TEST_ASSERT_EQUAL(0, fclose(f));
}