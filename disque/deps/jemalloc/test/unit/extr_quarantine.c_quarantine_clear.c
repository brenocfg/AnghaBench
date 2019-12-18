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
 int QUARANTINE_SIZE ; 
 int /*<<< orphan*/  assert_ptr_not_null (void*,char*) ; 
 int /*<<< orphan*/  dallocx (void*,int /*<<< orphan*/ ) ; 
 void* mallocx (int,int /*<<< orphan*/ ) ; 

void
quarantine_clear(void)
{
	void *p;

	p = mallocx(QUARANTINE_SIZE*2, 0);
	assert_ptr_not_null(p, "Unexpected mallocx() failure");
	dallocx(p, 0);
}