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
 char* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int hostfs_do_readlink (char*,char*,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*,char*) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 

__attribute__((used)) static char *follow_link(char *link)
{
	int len, n;
	char *name, *resolved, *end;

	len = 64;
	while (1) {
		n = -ENOMEM;
		name = kmalloc(len, GFP_KERNEL);
		if (name == NULL)
			goto out;

		n = hostfs_do_readlink(link, name, len);
		if (n < len)
			break;
		len *= 2;
		kfree(name);
	}
	if (n < 0)
		goto out_free;

	if (*name == '/')
		return name;

	end = strrchr(link, '/');
	if (end == NULL)
		return name;

	*(end + 1) = '\0';
	len = strlen(link) + strlen(name) + 1;

	resolved = kmalloc(len, GFP_KERNEL);
	if (resolved == NULL) {
		n = -ENOMEM;
		goto out_free;
	}

	sprintf(resolved, "%s%s", link, name);
	kfree(name);
	kfree(link);
	return resolved;

 out_free:
	kfree(name);
 out:
	return ERR_PTR(n);
}