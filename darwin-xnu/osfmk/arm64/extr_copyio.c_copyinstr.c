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
typedef  scalar_t__ vm_size_t ;
typedef  scalar_t__ user_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  COPYIO_INSTR ; 
 int ENAMETOOLONG ; 
 int copyin_validate (scalar_t__ const,uintptr_t,scalar_t__) ; 
 int copyio (int /*<<< orphan*/ ,char const*,char*,scalar_t__,scalar_t__*) ; 

int
copyinstr(const user_addr_t user_addr, char *kernel_addr, vm_size_t nbytes, vm_size_t *lencopied)
{
	int result;

	*lencopied = 0;
	if (nbytes == 0)
		return ENAMETOOLONG;

	result = copyin_validate(user_addr, (uintptr_t)kernel_addr, nbytes);

	if (result) return result;

	return copyio(COPYIO_INSTR, (const char *)(uintptr_t)user_addr, kernel_addr, nbytes, lencopied);
}