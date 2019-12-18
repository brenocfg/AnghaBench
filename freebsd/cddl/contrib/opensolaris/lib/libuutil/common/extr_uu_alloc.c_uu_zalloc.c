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
 int /*<<< orphan*/  UU_ERROR_SYSTEM ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  uu_set_error (int /*<<< orphan*/ ) ; 

void *
uu_zalloc(size_t n)
{
	void *p = malloc(n);

	if (p == NULL) {
		uu_set_error(UU_ERROR_SYSTEM);
		return (NULL);
	}

	(void) memset(p, 0, n);

	return (p);
}