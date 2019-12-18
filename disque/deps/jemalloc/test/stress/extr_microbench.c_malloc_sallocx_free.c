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
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int sallocx (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_fail (char*) ; 

__attribute__((used)) static void
malloc_sallocx_free(void)
{
	void *p;

	p = malloc(1);
	if (p == NULL) {
		test_fail("Unexpected malloc() failure");
		return;
	}
	if (sallocx(p, 0) < 1)
		test_fail("Unexpected sallocx() failure");
	free(p);
}