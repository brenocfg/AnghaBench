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
typedef  int /*<<< orphan*/  va_list ;
typedef  int /*<<< orphan*/  time_t ;
struct tm {int dummy; } ;

/* Variables and functions */
 int LOG_CONS ; 
 int LOG_FACMASK ; 
 int LOG_PERROR ; 
 int LOG_PID ; 
 int O_CLOEXEC ; 
 int O_NOCTTY ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  __openlog () ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (scalar_t__,void*,int) ; 
 int /*<<< orphan*/  dprintf (int,char*,int,char*) ; 
 int errno ; 
 int getpid () ; 
 int /*<<< orphan*/  gmtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  is_lost_conn (int) ; 
 int /*<<< orphan*/  log_addr ; 
 int log_facility ; 
 scalar_t__ log_fd ; 
 int /*<<< orphan*/  log_ident ; 
 int log_opt ; 
 int open (char*,int) ; 
 scalar_t__ send (scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 int snprintf (char*,int,char*,int,char*,int*,int /*<<< orphan*/ ,char*,int,char*) ; 
 int /*<<< orphan*/  strftime (char*,int,char*,struct tm*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int vsnprintf (char*,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _vsyslog(int priority, const char *message, va_list ap)
{
	char timebuf[16];
	time_t now;
	struct tm tm;
	char buf[1024];
	int errno_save = errno;
	int pid;
	int l, l2;
	int hlen;
	int fd;

	if (log_fd < 0) __openlog();

	if (!(priority & LOG_FACMASK)) priority |= log_facility;

	now = time(NULL);
	gmtime_r(&now, &tm);
	strftime(timebuf, sizeof timebuf, "%b %e %T", &tm);

	pid = (log_opt & LOG_PID) ? getpid() : 0;
	l = snprintf(buf, sizeof buf, "<%d>%s %n%s%s%.0d%s: ",
		priority, timebuf, &hlen, log_ident, "["+!pid, pid, "]"+!pid);
	errno = errno_save;
	l2 = vsnprintf(buf+l, sizeof buf - l, message, ap);
	if (l2 >= 0) {
		if (l2 >= sizeof buf - l) l = sizeof buf - 1;
		else l += l2;
		if (buf[l-1] != '\n') buf[l++] = '\n';
		if (send(log_fd, buf, l, 0) < 0 && (!is_lost_conn(errno)
		    || connect(log_fd, (void *)&log_addr, sizeof log_addr) < 0
		    || send(log_fd, buf, l, 0) < 0)
		    && (log_opt & LOG_CONS)) {
			fd = open("/dev/console", O_WRONLY|O_NOCTTY|O_CLOEXEC);
			if (fd >= 0) {
				dprintf(fd, "%.*s", l-hlen, buf+hlen);
				close(fd);
			}
		}
		if (log_opt & LOG_PERROR) dprintf(2, "%.*s", l-hlen, buf+hlen);
	}
}