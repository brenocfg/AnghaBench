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
typedef  int winsize ;
struct termios {int dummy; } ;

/* Variables and functions */
 int O_NOCTTY ; 
 int O_RDWR ; 
 int PTHREAD_CANCEL_DISABLE ; 
 int /*<<< orphan*/  TCSANOW ; 
 int /*<<< orphan*/  TIOCGPTN ; 
 int /*<<< orphan*/  TIOCSPTLCK ; 
 int /*<<< orphan*/  TIOCSWINSZ ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ ioctl (int,int /*<<< orphan*/ ,int const*) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  pthread_setcancelstate (int,int*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,struct termios const*) ; 

int openpty(int *pm, int *ps, char *name, const struct termios *tio, const struct winsize *ws)
{
	int m, s, n=0, cs;
	char buf[20];

	m = open("/dev/ptmx", O_RDWR|O_NOCTTY);
	if (m < 0) return -1;

	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &cs);

	if (ioctl(m, TIOCSPTLCK, &n) || ioctl (m, TIOCGPTN, &n))
		goto fail;

	if (!name) name = buf;
	snprintf(name, sizeof buf, "/dev/pts/%d", n);
	if ((s = open(name, O_RDWR|O_NOCTTY)) < 0)
		goto fail;

	if (tio) tcsetattr(s, TCSANOW, tio);
	if (ws) ioctl(s, TIOCSWINSZ, ws);

	*pm = m;
	*ps = s;

	pthread_setcancelstate(cs, 0);
	return 0;
fail:
	close(m);
	pthread_setcancelstate(cs, 0);
	return -1;
}