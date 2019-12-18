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
struct device_node {int dummy; } ;
typedef  int /*<<< orphan*/  phandle ;

/* Variables and functions */
 struct device_node* of_find_node_by_phandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char *parse_node(char *buf, size_t bufsize, struct device_node **npp)
{
	char *handle_str;
	phandle handle;
	*npp = NULL;

	handle_str = buf;

	buf = strchr(buf, ' ');
	if (!buf)
		return NULL;
	*buf = '\0';
	buf++;

	handle = simple_strtoul(handle_str, NULL, 0);

	*npp = of_find_node_by_phandle(handle);
	return buf;
}