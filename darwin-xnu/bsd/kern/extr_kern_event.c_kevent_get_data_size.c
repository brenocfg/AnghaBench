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
typedef  int /*<<< orphan*/  usize ;
typedef  scalar_t__ user_size_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  scalar_t__ user64_size_t ;
typedef  scalar_t__ user32_size_t ;
typedef  scalar_t__ uint64_t ;
struct proc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 unsigned int KEVENT_FLAG_KERNEL ; 
 scalar_t__ USER_ADDR_NULL ; 
 int copyin (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int
kevent_get_data_size(
		struct proc *p,
		uint64_t data_available,
		unsigned int flags,
		user_size_t *residp)
{
	user_size_t resid;
	int error = 0;

	if (data_available != USER_ADDR_NULL) {
		if (flags & KEVENT_FLAG_KERNEL) {
			resid = *(user_size_t *)(uintptr_t)data_available;
		} else if (IS_64BIT_PROCESS(p)) {
			user64_size_t usize;
			error = copyin((user_addr_t)data_available, &usize, sizeof(usize));
			resid = (user_size_t)usize;
		} else {
			user32_size_t usize;
			error = copyin((user_addr_t)data_available, &usize, sizeof(usize));
			resid = (user_size_t)usize;
		}
		if (error)
			return(error);
	} else {
		resid = 0;
	}
	*residp = resid;
	return 0;
}