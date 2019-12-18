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
 int /*<<< orphan*/  error_exit (char*,char) ; 

int check_atoi(char* str, int *result)
{
	int accum = 0;
	char* p = str;
	while(*p >= '0' && *p <= '9')
	{
		accum *= 10;
		accum += *p++ - '0';
	}
	if(*p != ' ' && *p != 0)
		error_exit("Malformed integer value (%c)", *p);
	*result = accum;
	return p - str;
}