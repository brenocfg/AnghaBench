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
 int /*<<< orphan*/  COPYIO_IN_WORD ; 
 int EINVAL ; 
 int copyin_validate (int const,uintptr_t,int) ; 
 int copyio (int /*<<< orphan*/ ,char const*,char*,int,int /*<<< orphan*/ *) ; 

int
copyin_word(const user_addr_t user_addr, uint64_t *kernel_addr, vm_size_t nbytes)
{
	int			result;

	/* Verify sizes */
	if ((nbytes != 4) && (nbytes != 8))
		return EINVAL;

	/* Test alignment */
	if (user_addr & (nbytes - 1))
		return EINVAL;

	result = copyin_validate(user_addr, (uintptr_t)kernel_addr, nbytes);
	if (result)
		return result;

	return copyio(COPYIO_IN_WORD, (const char *)user_addr, (char *)(uintptr_t)kernel_addr, nbytes, NULL);
}