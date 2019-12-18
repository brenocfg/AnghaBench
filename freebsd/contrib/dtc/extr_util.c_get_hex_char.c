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
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 
 long strtol (char*,char**,int) ; 

__attribute__((used)) static char get_hex_char(const char *s, int *i)
{
	char x[3];
	char *endx;
	long val;

	x[2] = '\0';
	strncpy(x, s + *i, 2);

	val = strtol(x, &endx, 16);
	if (!(endx  > x))
		die("\\x used with no following hex digits\n");

	(*i) += endx - x;
	return val;
}