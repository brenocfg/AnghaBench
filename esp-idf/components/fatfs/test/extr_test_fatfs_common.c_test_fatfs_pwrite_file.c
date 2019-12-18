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
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int open (char const*,int) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  test_file_content (char const*,char*) ; 
 int /*<<< orphan*/  test_pwrite (char const*,int /*<<< orphan*/ ,char*) ; 

void test_fatfs_pwrite_file(const char *filename)
{
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC);
    TEST_ASSERT_NOT_EQUAL(-1, fd);
    TEST_ASSERT_EQUAL(0, close(fd));

    test_pwrite(filename, 0, "Hello");
    test_file_content(filename, "Hello");

    test_pwrite(filename, strlen("Hello"), ", world!");
    test_file_content(filename, "Hello, world!");
    test_pwrite(filename, strlen("Hello, "), "Dolly");
    test_file_content(filename, "Hello, Dolly!");
}