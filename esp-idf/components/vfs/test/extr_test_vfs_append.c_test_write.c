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
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_MESSAGE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  write (int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void test_write(int fd, const char *str, const char *msg)
{
    TEST_ASSERT_EQUAL_MESSAGE(strlen(str), write(fd, str, strlen(str)), msg);
}