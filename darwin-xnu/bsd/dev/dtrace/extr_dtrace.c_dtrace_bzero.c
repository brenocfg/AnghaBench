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
typedef  int /*<<< orphan*/  uchar_t ;

/* Variables and functions */

__attribute__((used)) static void
dtrace_bzero(void *dst, size_t len)
{
	uchar_t *cp;

	for (cp = dst; len != 0; len--)
		*cp++ = 0;
}