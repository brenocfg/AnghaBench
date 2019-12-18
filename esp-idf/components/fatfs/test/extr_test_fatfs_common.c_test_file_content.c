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
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int,int const) ; 
 int /*<<< orphan*/  close (int const) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int read (int const,char*,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static void test_file_content(const char *filename, const char *msg)
{
    char buf[32] = { 0 };
    const int fd = open(filename, O_RDONLY);
    TEST_ASSERT_NOT_EQUAL(-1, fd);

    int r = read(fd, buf, sizeof(buf));
    TEST_ASSERT_NOT_EQUAL(-1, r);
    TEST_ASSERT_EQUAL(0, strcmp(msg, buf));

    TEST_ASSERT_EQUAL(0, close(fd));
}