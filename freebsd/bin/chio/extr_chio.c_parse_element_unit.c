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
typedef  int /*<<< orphan*/  u_int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  errx (int,char*,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static u_int16_t
parse_element_unit(char *cp)
{
	int i;
	char *p;

	i = (int)strtol(cp, &p, 10);
	if ((i < 0) || (*p != '\0'))
		errx(1, "invalid unit number `%s'", cp);

	return ((u_int16_t)i);
}