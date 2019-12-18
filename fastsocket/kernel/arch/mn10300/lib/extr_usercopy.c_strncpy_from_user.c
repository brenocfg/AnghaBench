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
 long EFAULT ; 
 int /*<<< orphan*/  VERIFY_READ ; 
 int /*<<< orphan*/  __do_strncpy_from_user (char*,char const*,long,long) ; 
 scalar_t__ access_ok (int /*<<< orphan*/ ,char const*,int) ; 

long
strncpy_from_user(char *dst, const char *src, long count)
{
	long res = -EFAULT;
	if (access_ok(VERIFY_READ, src, 1))
		__do_strncpy_from_user(dst, src, count, res);
	return res;
}