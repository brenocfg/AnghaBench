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
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_MESSAGE (int,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE (char const*,char*,int,char const*) ; 
 int /*<<< orphan*/  read (int,char*,int) ; 
 int strlen (char const*) ; 

__attribute__((used)) static inline void test_read(int fd, const char *str, const char *msg)
{
    char buf[strlen(str)];
    TEST_ASSERT_EQUAL_MESSAGE(strlen(str), read(fd, buf, strlen(str)), msg);
    TEST_ASSERT_EQUAL_UINT8_ARRAY_MESSAGE(str, buf, strlen(str), msg);
}