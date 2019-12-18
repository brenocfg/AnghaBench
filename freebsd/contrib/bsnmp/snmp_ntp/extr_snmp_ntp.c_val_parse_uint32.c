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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ u_long ;

/* Variables and functions */
 scalar_t__ errno ; 
 scalar_t__ strtoul (char const*,char**,int) ; 

__attribute__((used)) static int
val_parse_uint32(const char *val, uint32_t *p, uint32_t min, uint32_t max,
    int base)
{
	u_long n;
	char *end;

	errno = 0;
	n = strtoul(val, &end, base);
	if (errno != 0 || *end != '\0')
		return (0);
	if (n < min || n > max)
		return (0);
	*p = (uint32_t)n;
	return (1);
}