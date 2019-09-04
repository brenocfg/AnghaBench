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
typedef  int vm_size_t ;
typedef  int user_addr_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  COPYINWORD ; 
 int EINVAL ; 
 int copyio (int /*<<< orphan*/ ,int const,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
copyin_word(const user_addr_t user_addr, uint64_t *kernel_addr, vm_size_t nbytes)
{
	/* Verify sizes */
	if ((nbytes != 4) && (nbytes != 8))
		return EINVAL;

	/* Test alignment */
	if (user_addr & (nbytes - 1))
		return EINVAL;
	return copyio(COPYINWORD, user_addr, (char *)(uintptr_t)kernel_addr, nbytes, NULL, 0);
}