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
 int /*<<< orphan*/  AUTHPRNT (char*) ; 
 int EINVAL ; 
 int ENOMEM ; 
 size_t MAXPATHLEN ; 
 char* kalloc (size_t) ; 
 int /*<<< orphan*/  kfree_safe (char*) ; 
 size_t strlcat (char*,char*,size_t) ; 
 size_t strlcpy (char*,char const*,size_t) ; 
 size_t strlen (char*) ; 
 size_t strnlen (char const*,size_t) ; 

__attribute__((used)) static int
construct_chunklist_path(const char *root_path, char **bufp)
{
	int err = 0;
	char *path = NULL;
	size_t len = 0;

	path = kalloc(MAXPATHLEN);
	if (path == NULL) {
		AUTHPRNT("failed to allocate space for chunklist path");
		err = ENOMEM;
		goto out;
	}

	len = strnlen(root_path, MAXPATHLEN);
	if (len < MAXPATHLEN && len > strlen(".dmg")) {
		/* correctly terminated string with space for extension */
	} else {
		AUTHPRNT("malformed root path");
		err = EINVAL;
		goto out;
	}

	len = strlcpy(path, root_path, MAXPATHLEN);
	if (len >= MAXPATHLEN) {
		AUTHPRNT("root path is too long");
		err = EINVAL;
		goto out;
	}

	path[len - strlen(".dmg")] = '\0';
	len = strlcat(path, ".chunklist", MAXPATHLEN);
	if (len >= MAXPATHLEN) {
		AUTHPRNT("chunklist path is too long");
		err = EINVAL;
		goto out;
	}

out:
	if (err) {
		kfree_safe(path);
	} else {
		*bufp = path;
	}
	return err;
}