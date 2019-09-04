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
 int /*<<< orphan*/  ARM_PGBYTES ; 
 int /*<<< orphan*/  __nosan_bzero (void*,int /*<<< orphan*/ ) ; 
 uintptr_t alloc_page () ; 
 scalar_t__ phystokv (uintptr_t) ; 

__attribute__((used)) static uintptr_t
alloc_zero_page(void)
{
	uintptr_t mem = alloc_page();
	__nosan_bzero((void *)phystokv(mem), ARM_PGBYTES);
	return mem;
}