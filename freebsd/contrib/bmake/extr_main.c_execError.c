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
struct iovec {int dummy; } ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 int /*<<< orphan*/  IOADD (char const*) ; 
 scalar_t__ errno ; 
 char* progname ; 
 char* strerror (scalar_t__) ; 
 int writev (int,struct iovec*,int) ; 

void
execError(const char *af, const char *av)
{
#ifdef USE_IOVEC
	int i = 0;
	struct iovec iov[8];
#define IOADD(s) \
	(void)(iov[i].iov_base = UNCONST(s), \
	    iov[i].iov_len = strlen(iov[i].iov_base), \
	    i++)
#else
#define	IOADD(s) (void)write(2, s, strlen(s))
#endif

	IOADD(progname);
	IOADD(": ");
	IOADD(af);
	IOADD("(");
	IOADD(av);
	IOADD(") failed (");
	IOADD(strerror(errno));
	IOADD(")\n");

#ifdef USE_IOVEC
	while (writev(2, iov, 8) == -1 && errno == EAGAIN)
	    continue;
#endif
}