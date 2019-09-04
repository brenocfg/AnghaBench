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
typedef  int uintmax_t ;

/* Variables and functions */
 int ULONG_MAX ; 

__attribute__((used)) static char *fmt_u(uintmax_t x, char *s)
{
	unsigned long y;
	for (   ; x>ULONG_MAX; x/=10) *--s = '0' + x%10;
	for (y=x;           y; y/=10) *--s = '0' + y%10;
	return s;
}