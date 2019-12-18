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
struct csrctl_args {scalar_t__ useraddr; int usersize; } ;
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  csr_config_t ;

/* Variables and functions */
 int EINVAL ; 
 int copyin (scalar_t__,int /*<<< orphan*/ *,int) ; 
 int csr_check (int /*<<< orphan*/ ) ; 

int
syscall_csr_check(struct csrctl_args *args)
{
	csr_config_t mask = 0;
	int error = 0;

	if (args->useraddr == 0 || args->usersize != sizeof(mask))
		return EINVAL;

	error = copyin(args->useraddr, &mask, sizeof(mask));
	if (error)
		return error;

	return csr_check(mask);
}