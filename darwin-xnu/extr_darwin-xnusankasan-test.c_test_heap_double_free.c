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
 int /*<<< orphan*/  BUFSZ ; 
 int /*<<< orphan*/  TEST_FAULT (struct kasan_test*) ; 
 int /*<<< orphan*/  TEST_START (struct kasan_test*) ; 
 int /*<<< orphan*/ * kalloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_heap_double_free(struct kasan_test *t)
{
	TEST_START(t);

	uint8_t *x = kalloc(BUFSZ);
	if (!x) {
		return 1;
	}
	kfree(x, BUFSZ);

	TEST_FAULT(t);
	kfree(x, BUFSZ);

	return 0;
}