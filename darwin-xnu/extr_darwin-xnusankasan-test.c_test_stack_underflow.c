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
 int /*<<< orphan*/  __nosan_memset (int*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int test_stack_underflow(struct kasan_test *t)
{
	TEST_START(t);

	long idx;
	uint8_t a[STACK_ARRAY_SZ];

	__nosan_memset(a, 0, STACK_ARRAY_SZ);

	/* generate a negative index without the compiler noticing */
#if __x86_64__
	__asm__ __volatile__("movq $-1, %0" : "=r"(idx) :: "memory");
#else
	__asm__ __volatile__("mov %0, #-1" : "=r"(idx) :: "memory");
#endif

	TEST_FAULT(t);
	a[idx] = 0xbd;
	TEST_NOFAULT(t);

	TEST_BARRIER();
	return (a[0] == 0);
}