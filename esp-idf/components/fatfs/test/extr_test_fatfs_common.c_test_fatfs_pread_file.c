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

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int,int) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int,int const) ; 
 int close (int const) ; 
 scalar_t__ fatfs_test_hello_str ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int pread (int const,char*,int,int) ; 
 int read (int const,char*,int) ; 
 int strcmp (scalar_t__,char*) ; 
 int strlen (scalar_t__) ; 

void test_fatfs_pread_file(const char* filename)
{
    char buf[32] = { 0 };
    const int fd = open(filename, O_RDONLY);
    TEST_ASSERT_NOT_EQUAL(-1, fd);

    int r = pread(fd, buf, sizeof(buf), 0); // it is a regular read() with offset==0
    TEST_ASSERT_EQUAL(0, strcmp(fatfs_test_hello_str, buf));
    TEST_ASSERT_EQUAL(strlen(fatfs_test_hello_str), r);

    memset(buf, 0, sizeof(buf));
    r = pread(fd, buf, sizeof(buf), 1); // offset==1
    TEST_ASSERT_EQUAL(0, strcmp(fatfs_test_hello_str + 1, buf));
    TEST_ASSERT_EQUAL(strlen(fatfs_test_hello_str) - 1, r);

    memset(buf, 0, sizeof(buf));
    r = pread(fd, buf, sizeof(buf), 5); // offset==5
    TEST_ASSERT_EQUAL(0, strcmp(fatfs_test_hello_str + 5, buf));
    TEST_ASSERT_EQUAL(strlen(fatfs_test_hello_str) - 5, r);

    // regular read() should work now because pread() should not affect the current position in file

    memset(buf, 0, sizeof(buf));
    r = read(fd, buf, sizeof(buf)); // note that this is read() and not pread()
    TEST_ASSERT_EQUAL(0, strcmp(fatfs_test_hello_str, buf));
    TEST_ASSERT_EQUAL(strlen(fatfs_test_hello_str), r);

    memset(buf, 0, sizeof(buf));
    r = pread(fd, buf, sizeof(buf), 10); // offset==10
    TEST_ASSERT_EQUAL(0, strcmp(fatfs_test_hello_str + 10, buf));
    TEST_ASSERT_EQUAL(strlen(fatfs_test_hello_str) - 10, r);

    memset(buf, 0, sizeof(buf));
    r = pread(fd, buf, sizeof(buf), strlen(fatfs_test_hello_str) + 1); // offset to EOF
    TEST_ASSERT_EQUAL(0, r);

    TEST_ASSERT_EQUAL(0, close(fd));
}