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
typedef  int /*<<< orphan*/  user_size_t ;
typedef  int /*<<< orphan*/  user_addr_t ;
typedef  int /*<<< orphan*/  user64_size_t ;
typedef  int /*<<< orphan*/  user32_size_t ;
typedef  scalar_t__ uint64_t ;
struct proc {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_64BIT_PROCESS (struct proc*) ; 
 unsigned int KEVENT_FLAG_KERNEL ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
kevent_put_data_size(
		struct proc *p,
		uint64_t data_available,
		unsigned int flags,
		user_size_t resid)
{
	int error = 0;

	if (data_available) {
		if (flags & KEVENT_FLAG_KERNEL) {
			*(user_size_t *)(uintptr_t)data_available = resid;
		} else if (IS_64BIT_PROCESS(p)) {
			user64_size_t usize = (user64_size_t)resid;
			error = copyout(&usize, (user_addr_t)data_available, sizeof(usize));
		} else {
			user32_size_t usize = (user32_size_t)resid;
			error = copyout(&usize, (user_addr_t)data_available, sizeof(usize));
		}
	}
	return error;
}