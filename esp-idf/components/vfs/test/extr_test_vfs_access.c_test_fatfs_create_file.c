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

__attribute__((used)) static inline void test_fatfs_create_file(const char *name)
{
    int fd = open(name, O_WRONLY | O_CREAT | O_TRUNC);
    TEST_ASSERT_NOT_EQUAL(fd, -1);
    TEST_ASSERT_EQUAL(0, close(fd));
}