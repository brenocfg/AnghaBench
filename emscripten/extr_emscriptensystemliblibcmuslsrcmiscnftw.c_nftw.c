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
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int PATH_MAX ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int do_nftw (char*,int (*) (char const*,struct stat const*,int,struct FTW*),int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 
 size_t strlen (char const*) ; 

int nftw(const char *path, int (*fn)(const char *, const struct stat *, int, struct FTW *), int fd_limit, int flags)
{
	int r, cs;
	size_t l;
	char pathbuf[PATH_MAX+1];

	if (fd_limit <= 0) return 0;

	l = strlen(path);
	if (l > PATH_MAX) {
		errno = ENAMETOOLONG;
		return -1;
	}
	memcpy(pathbuf, path, l+1);
	
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
	r = do_nftw(pathbuf, fn, fd_limit, flags, NULL);
	pthread_setcancelstate(cs, 0);
	return r;
}