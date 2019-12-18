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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  array_free (void**,int) ; 
 void* kzalloc (size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void *array_zalloc(int n, size_t size, gfp_t flags)
{
	void **a;
	int i;

	a = kzalloc(n * sizeof(void*), flags);
	if (!a)
		return NULL;
	for (i = 0; i < n; i++) {
		a[i] = kzalloc(size, flags);
		if (!a[i]) {
			array_free(a, n);
			return NULL;
		}
	}
	return a;
}