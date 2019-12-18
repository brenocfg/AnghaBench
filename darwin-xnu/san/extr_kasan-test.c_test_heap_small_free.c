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
struct kasan_test {scalar_t__ datasz; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 scalar_t__ BUFSZ ; 
 int /*<<< orphan*/  TEST_FAULT (struct kasan_test*) ; 
 int /*<<< orphan*/  TEST_START (struct kasan_test*) ; 
 int /*<<< orphan*/ * kalloc (scalar_t__) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int test_heap_small_free(struct kasan_test *t)
{
	TEST_START(t);

	uint8_t *x = kalloc(BUFSZ);
	if (!x) {
		return 1;
	}
	t->datasz = BUFSZ;
	t->data = x;

	TEST_FAULT(t);
	kfree(x, BUFSZ-2);
	t->data = NULL;
	t->datasz = 0;

	return 0;
}