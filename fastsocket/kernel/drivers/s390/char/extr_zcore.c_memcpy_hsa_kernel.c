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
 int /*<<< orphan*/  TO_KERNEL ; 
 int memcpy_hsa (void*,unsigned long,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int memcpy_hsa_kernel(void *dest, unsigned long src, size_t count)
{
	return memcpy_hsa(dest, src, count, TO_KERNEL);
}