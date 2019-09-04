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
 int /*<<< orphan*/  strncat (char*,char*,int) ; 

__attribute__((used)) static int test_strncat(struct kasan_test *t)
{
	TEST_START(t);
	char a1[9] = {};

	/* should not fault */
	strncat(a1, "abcd", 4);
	strncat(a1, "efgh", 4);

	TEST_FAULT(t);
	strncat(a1, "i", 1);
	TEST_NOFAULT(t);

	return a1[0] != 'a';
}