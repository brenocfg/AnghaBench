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
struct kasan_test {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TEST_FAULT (struct kasan_test*) ; 
 int /*<<< orphan*/  TEST_NOFAULT (struct kasan_test*) ; 
 int /*<<< orphan*/  TEST_START (struct kasan_test*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static int test_strlcpy(struct kasan_test *t)
{
	TEST_START(t);
	char a1[8];

	/* should not fault */
	strlcpy(a1, "small", 8);
	strlcpy(a1, "looooonnnnggg", 8);

	TEST_FAULT(t);
	strlcpy(a1, "looooooooonnnnggg", 9);
	TEST_NOFAULT(t);

	return 0;
}