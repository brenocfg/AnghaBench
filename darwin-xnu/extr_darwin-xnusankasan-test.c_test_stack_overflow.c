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
typedef  int uint8_t ;
struct kasan_test {int dummy; } ;

/* Variables and functions */
 int STACK_ARRAY_SZ ; 
 int /*<<< orphan*/  TEST_BARRIER () ; 
 int /*<<< orphan*/  TEST_FAULT (struct kasan_test*) ; 
 int /*<<< orphan*/  TEST_NOFAULT (struct kasan_test*) ; 
 int /*<<< orphan*/  TEST_START (struct kasan_test*) ; 

__attribute__((used)) static int test_stack_overflow(struct kasan_test *t)
{
	TEST_START(t);

	int i;
	volatile uint8_t a[STACK_ARRAY_SZ];

	for (i = 0; i < STACK_ARRAY_SZ; i++) {
		a[i] = i;
	}

	TEST_FAULT(t);
	a[i] = i; /* rookie error */
	TEST_NOFAULT(t);

	TEST_BARRIER();

	return !(a[0] == 0);
}