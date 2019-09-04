#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t _a_stacksize; size_t _a_stackaddr; } ;
typedef  TYPE_1__ pthread_attr_t ;

/* Variables and functions */
 size_t DEFAULT_STACK_SIZE ; 
 int EINVAL ; 

int pthread_attr_getstack(const pthread_attr_t *restrict a, void **restrict addr, size_t *restrict size)
{
/// XXX musl is not standard-conforming? It should not report EINVAL if _a_stackaddr is zero, and it should
///     report EINVAL if a is null: http://pubs.opengroup.org/onlinepubs/009695399/functions/pthread_attr_getstack.html
	if (!a) return EINVAL;
//	if (!a->_a_stackaddr)
//		return EINVAL;

	*size = a->_a_stacksize + DEFAULT_STACK_SIZE;
	*addr = (void *)(a->_a_stackaddr - *size);
	return 0;
}