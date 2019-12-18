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
 int ENOMEM ; 
 int ENOSPC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kmalloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int parse_name(char **pname, const char *token)
{
	size_t len;
	char *name;

	len = strlen(token) + 1;
	if (len > 64)
		return -ENOSPC;

	name = kmalloc(len, GFP_KERNEL);
	if (!name)
		return -ENOMEM;

	strcpy(name, token);

	*pname = name;
	return 0;
}