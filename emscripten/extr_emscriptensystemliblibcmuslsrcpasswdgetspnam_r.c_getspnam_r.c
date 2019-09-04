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
struct stat {int /*<<< orphan*/  st_mode; int /*<<< orphan*/  member_0; } ;
struct spwd {int dummy; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  NAME_MAX ; 
 int O_CLOEXEC ; 
 int O_NOFOLLOW ; 
 int O_NONBLOCK ; 
 int O_RDONLY ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ __parsespent (char*,struct spwd*) ; 
 int /*<<< orphan*/  cleanup ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/ * fdopen (int,char*) ; 
 scalar_t__ fgets (char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 scalar_t__ fstat (int,struct stat*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  pthread_cleanup_pop (int) ; 
 int /*<<< orphan*/  pthread_cleanup_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 
 int snprintf (char*,int,char*,char const*) ; 
 scalar_t__ strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,size_t) ; 

int getspnam_r(const char *name, struct spwd *sp, char *buf, size_t size, struct spwd **res)
{
	char path[20+NAME_MAX];
	FILE *f = 0;
	int rv = 0;
	int fd;
	size_t k, l = strlen(name);
	int skip = 0;
	int cs;

	*res = 0;

	/* Disallow potentially-malicious user names */
	if (*name=='.' || strchr(name, '/') || !l)
		return EINVAL;

	/* Buffer size must at least be able to hold name, plus some.. */
	if (size < l+100) return ERANGE;

	/* Protect against truncation */
	if (snprintf(path, sizeof path, "/etc/tcb/%s/shadow", name) >= sizeof path)
		return EINVAL;

	fd = open(path, O_RDONLY|O_NOFOLLOW|O_NONBLOCK|O_CLOEXEC);
	if (fd >= 0) {
		struct stat st = { 0 };
		errno = EINVAL;
		if (fstat(fd, &st) || !S_ISREG(st.st_mode) || !(f = fdopen(fd, "rb"))) {
			pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);
			close(fd);
			pthread_setcancelstate(cs, 0);
			return errno;
		}
	} else {
		f = fopen("/etc/shadow", "rbe");
		if (!f) return errno;
	}

	pthread_cleanup_push(cleanup, f);
	while (fgets(buf, size, f) && (k=strlen(buf))>0) {
		if (skip || strncmp(name, buf, l) || buf[l]!=':') {
			skip = buf[k-1] != '\n';
			continue;
		}
		if (buf[k-1] != '\n') {
			rv = ERANGE;
			break;
		}

		if (__parsespent(buf, sp) < 0) continue;
		*res = sp;
		break;
	}
	pthread_cleanup_pop(1);
	return rv;
}