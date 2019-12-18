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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  __doprnt (char const*,int /*<<< orphan*/ ,void (*) (int,void*),void*,int,int /*<<< orphan*/ ) ; 

int
kvprintf(char const *fmt, void (*func)(int, void*), void *arg, int radix, va_list ap)
{
	__doprnt(fmt, ap, func, arg, radix, TRUE);
	return 0;
}