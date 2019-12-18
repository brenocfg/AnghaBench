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
typedef  int off_t ;

/* Variables and functions */
 int /*<<< orphan*/  O_WRONLY ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL (int const,int const) ; 
 int /*<<< orphan*/  TEST_ASSERT_NOT_EQUAL (int,int const) ; 
 int const close (int const) ; 
 int const lseek (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int pwrite (int const,char const*,int const,int) ; 
 int const strlen (char const*) ; 

__attribute__((used)) static void test_pwrite(const char *filename, off_t offset, const char *msg)
{
    const int fd = open(filename, O_WRONLY);
    TEST_ASSERT_NOT_EQUAL(-1, fd);

    const off_t current_pos = lseek(fd, 0, SEEK_END); // O_APPEND is not the same - jumps to the end only before write()

    const int r = pwrite(fd, msg, strlen(msg), offset);
    TEST_ASSERT_EQUAL(strlen(msg), r);

    TEST_ASSERT_EQUAL(current_pos, lseek(fd, 0, SEEK_CUR)); // pwrite should not move the pointer

    TEST_ASSERT_EQUAL(0, close(fd));
}