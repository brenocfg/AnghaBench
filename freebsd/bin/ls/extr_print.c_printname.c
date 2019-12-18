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
 scalar_t__ f_nonprint ; 
 scalar_t__ f_octal ; 
 scalar_t__ f_octal_escape ; 
 int prn_normal (char const*) ; 
 int prn_octal (char const*) ; 
 int prn_printable (char const*) ; 

int
printname(const char *name)
{
	if (f_octal || f_octal_escape)
		return prn_octal(name);
	else if (f_nonprint)
		return prn_printable(name);
	else
		return prn_normal(name);
}