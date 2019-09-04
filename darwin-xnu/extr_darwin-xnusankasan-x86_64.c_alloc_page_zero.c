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
 int /*<<< orphan*/  I386_PGBYTES ; 
 uintptr_t alloc_page () ; 
 int /*<<< orphan*/  bzero_phys (uintptr_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uintptr_t
alloc_page_zero(void)
{
	uintptr_t mem = alloc_page();
	bzero_phys(mem, I386_PGBYTES);
	return mem;
}