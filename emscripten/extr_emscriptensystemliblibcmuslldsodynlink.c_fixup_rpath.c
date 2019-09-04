#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct dso {char* rpath; char const* rpath_orig; char* name; scalar_t__ kernel_mapped; } ;
struct TYPE_2__ {scalar_t__ secure; } ;

/* Variables and functions */
#define  EACCES 130 
#define  ENOENT 129 
#define  ENOTDIR 128 
 size_t PATH_MAX ; 
 size_t SSIZE_MAX ; 
 int errno ; 
 TYPE_1__ libc ; 
 char* malloc (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 size_t readlink (char*,char*,size_t) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strrchr (char const*,char) ; 

__attribute__((used)) static int fixup_rpath(struct dso *p, char *buf, size_t buf_size)
{
	size_t n, l;
	const char *s, *t, *origin;
	char *d;
	if (p->rpath || !p->rpath_orig) return 0;
	if (!strchr(p->rpath_orig, '$')) {
		p->rpath = p->rpath_orig;
		return 0;
	}
	n = 0;
	s = p->rpath_orig;
	while ((t=strchr(s, '$'))) {
		if (strncmp(t, "$ORIGIN", 7) && strncmp(t, "${ORIGIN}", 9))
			return 0;
		s = t+1;
		n++;
	}
	if (n > SSIZE_MAX/PATH_MAX) return 0;

	if (p->kernel_mapped) {
		/* $ORIGIN searches cannot be performed for the main program
		 * when it is suid/sgid/AT_SECURE. This is because the
		 * pathname is under the control of the caller of execve.
		 * For libraries, however, $ORIGIN can be processed safely
		 * since the library's pathname came from a trusted source
		 * (either system paths or a call to dlopen). */
		if (libc.secure)
			return 0;
		l = readlink("/proc/self/exe", buf, buf_size);
		if (l == -1) switch (errno) {
		case ENOENT:
		case ENOTDIR:
		case EACCES:
			break;
		default:
			return -1;
		}
		if (l >= buf_size)
			return 0;
		buf[l] = 0;
		origin = buf;
	} else {
		origin = p->name;
	}
	t = strrchr(origin, '/');
	l = t ? t-origin : 0;
	p->rpath = malloc(strlen(p->rpath_orig) + n*l + 1);
	if (!p->rpath) return -1;

	d = p->rpath;
	s = p->rpath_orig;
	while ((t=strchr(s, '$'))) {
		memcpy(d, s, t-s);
		d += t-s;
		memcpy(d, origin, l);
		d += l;
		/* It was determined previously that the '$' is followed
		 * either by "ORIGIN" or "{ORIGIN}". */
		s = t + 7 + 2*(t[1]=='{');
	}
	strcpy(d, s);
	return 0;
}