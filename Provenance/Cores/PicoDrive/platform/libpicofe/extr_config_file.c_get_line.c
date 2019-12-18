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
 int /*<<< orphan*/  mystrip (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,size_t) ; 

__attribute__((used)) static void get_line(char *d, size_t size, const char *s)
{
	const char *pe;
	size_t len;

	for (pe = s; *pe != '\r' && *pe != '\n' && *pe != 0; pe++)
		;
	len = pe - s;
	if (len > size - 1)
		len = size - 1;
	strncpy(d, s, len);
	d[len] = 0;

	mystrip(d);
}