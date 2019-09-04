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
typedef  int /*<<< orphan*/  uint8_t ;
struct kasan_test {int dummy; } ;

/* Variables and functions */
 int STACK_ARRAY_SZ ; 
 int /*<<< orphan*/  TEST_BARRIER () ; 
 int /*<<< orphan*/  TEST_FAULT (struct kasan_test*) ; 
 int /*<<< orphan*/  TEST_NOFAULT (struct kasan_test*) ; 
 int /*<<< orphan*/  TEST_START (struct kasan_test*) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int test_bzero(struct kasan_test *t)
{
	TEST_START(t);
	uint8_t a1[STACK_ARRAY_SZ];

	/* should work */
	bzero(a1, STACK_ARRAY_SZ);

	TEST_BARRIER();

	/* should fail */
	TEST_FAULT(t);
	bzero(a1, STACK_ARRAY_SZ+1);
	TEST_NOFAULT(t);

	return 0;
}