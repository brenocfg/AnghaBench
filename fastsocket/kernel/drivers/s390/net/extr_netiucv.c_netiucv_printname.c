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
 int /*<<< orphan*/  isspace (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static char *netiucv_printname(char *name)
{
	static char tmp[9];
	char *p = tmp;
	memcpy(tmp, name, 8);
	tmp[8] = '\0';
	while (*p && (!isspace(*p)))
		p++;
	*p = '\0';
	return tmp;
}