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
 int /*<<< orphan*/  CONFIG_CHUNK (char*,int,int,char*,int) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uml_physmem ; 

__attribute__((used)) static int mem_get_config(char *name, char *str, int size, char **error_out)
{
	char buf[sizeof("18446744073709551615")];
	int len = 0;

	sprintf(buf, "%ld", uml_physmem);
	CONFIG_CHUNK(str, size, len, buf, 1);

	return len;
}