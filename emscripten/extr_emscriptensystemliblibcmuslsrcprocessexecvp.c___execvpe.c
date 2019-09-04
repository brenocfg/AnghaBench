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
 scalar_t__ EACCES ; 
 scalar_t__ ENAMETOOLONG ; 
 scalar_t__ ENOENT ; 
 int NAME_MAX ; 
 int PATH_MAX ; 
 scalar_t__ errno ; 
 int execve (char const*,char* const*,char* const*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* strchr (char const*,char) ; 
 int strlen (char const*) ; 
 int strnlen (char const*,int) ; 

int __execvpe(const char *file, char *const argv[], char *const envp[])
{
	const char *p, *z, *path = getenv("PATH");
	size_t l, k;
	int seen_eacces = 0;

	errno = ENOENT;
	if (!*file) return -1;

	if (strchr(file, '/'))
		return execve(file, argv, envp);

	if (!path) path = "/usr/local/bin:/bin:/usr/bin";
	k = strnlen(file, NAME_MAX+1);
	if (k > NAME_MAX) {
		errno = ENAMETOOLONG;
		return -1;
	}
	l = strnlen(path, PATH_MAX-1)+1;

	for(p=path; ; p=z) {
		char b[l+k+1];
		z = strchr(p, ':');
		if (!z) z = p+strlen(p);
		if (z-p >= l) {
			if (!*z++) break;
			continue;
		}
		memcpy(b, p, z-p);
		b[z-p] = '/';
		memcpy(b+(z-p)+(z>p), file, k+1);
		execve(b, argv, envp);
		if (errno == EACCES) seen_eacces = 1;
		else if (errno != ENOENT) return -1;
		if (!*z++) break;
	}
	if (seen_eacces) errno = EACCES;
	return -1;
}