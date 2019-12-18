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
 int /*<<< orphan*/  VERIFY_READ ; 
 int /*<<< orphan*/  __copy_user_zeroing (void*,void const*,unsigned long) ; 
 scalar_t__ access_ok (int /*<<< orphan*/ ,void const*,unsigned long) ; 

unsigned long
__generic_copy_from_user(void *to, const void *from, unsigned long n)
{
	if (access_ok(VERIFY_READ, from, n))
		__copy_user_zeroing(to, from, n);
	return n;
}