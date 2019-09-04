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
struct stat {int st_mode; } ;
struct match {int dummy; } ;
struct dirent {size_t d_reclen; char const* d_name; int d_type; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int EACCES ; 
 int ENOTDIR ; 
 int FNM_NOESCAPE ; 
 int FNM_PERIOD ; 
 int GLOB_ABORTED ; 
 int GLOB_ERR ; 
 int GLOB_MARK ; 
 int GLOB_NOESCAPE ; 
 int GLOB_NOSPACE ; 
 int GLOB_PERIOD ; 
 int S_ISDIR (int) ; 
 int /*<<< orphan*/  S_ISLNK (int) ; 
 scalar_t__ append (struct match**,char const*,size_t,int) ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int errno ; 
 scalar_t__ fnmatch (char const*,char const*,int) ; 
 int is_literal (char const*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/ * opendir (char const*) ; 
 int readdir_r (int /*<<< orphan*/ *,struct dirent*,struct dirent**) ; 
 int /*<<< orphan*/  stat (char const*,struct stat*) ; 
 char* strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static int match_in_dir(const char *d, const char *p, int flags, int (*errfunc)(const char *path, int err), struct match **tail)
{
	DIR *dir;
	struct dirent de_buf, *de;
	char pat[strlen(p)+1];
	char *p2;
	size_t l = strlen(d);
	int literal;
	int fnm_flags= ((flags & GLOB_NOESCAPE) ? FNM_NOESCAPE : 0)
		| ((!(flags & GLOB_PERIOD)) ? FNM_PERIOD : 0);
	int error;

	if ((p2 = strchr(p, '/'))) {
		strcpy(pat, p);
		pat[p2-p] = 0;
		for (; *p2 == '/'; p2++);
		p = pat;
	}
	literal = is_literal(p, !(flags & GLOB_NOESCAPE));
	if (*d == '/' && !*(d+1)) l = 0;

	/* rely on opendir failing for nondirectory objects */
	dir = opendir(*d ? d : ".");
	error = errno;
	if (!dir) {
		/* this is not an error -- we let opendir call stat for us */
		if (error == ENOTDIR) return 0;
		if (error == EACCES && !*p) {
			struct stat st;
			if (!stat(d, &st) && S_ISDIR(st.st_mode)) {
				if (append(tail, d, l, l))
					return GLOB_NOSPACE;
				return 0;
			}
		}
		if (errfunc(d, error) || (flags & GLOB_ERR))
			return GLOB_ABORTED;
		return 0;
	}
	if (!*p) {
		error = append(tail, d, l, l) ? GLOB_NOSPACE : 0;
		closedir(dir);
		return error;
	}
	while (!(error = readdir_r(dir, &de_buf, &de)) && de) {
		char namebuf[l+de->d_reclen+2], *name = namebuf;
		if (!literal && fnmatch(p, de->d_name, fnm_flags))
			continue;
		if (literal && strcmp(p, de->d_name))
			continue;
		if (p2 && de->d_type && !S_ISDIR(de->d_type<<12) && !S_ISLNK(de->d_type<<12))
			continue;
		if (*d) {
			memcpy(name, d, l);
			name[l] = '/';
			strcpy(name+l+1, de->d_name);
		} else {
			name = de->d_name;
		}
		if (p2) {
			if ((error = match_in_dir(name, p2, flags, errfunc, tail))) {
				closedir(dir);
				return error;
			}
		} else {
			int mark = 0;
			if (flags & GLOB_MARK) {
				if (de->d_type && !S_ISLNK(de->d_type<<12))
					mark = S_ISDIR(de->d_type<<12);
				else {
					struct stat st;
					stat(name, &st);
					mark = S_ISDIR(st.st_mode);
				}
			}
			if (append(tail, name, l+de->d_reclen+1, mark)) {
				closedir(dir);
				return GLOB_NOSPACE;
			}
		}
	}
	closedir(dir);
	if (error && (errfunc(d, error) || (flags & GLOB_ERR)))
		return GLOB_ABORTED;
	return 0;
}