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
struct termios {int c_lflag; int c_iflag; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int ECHO ; 
 int ICANON ; 
 int ICRNL ; 
 int IGNCR ; 
 int INLCR ; 
 int ISIG ; 
 int O_CLOEXEC ; 
 int O_NOCTTY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dprintf (int,char*,...) ; 
 int open (char*,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  tcdrain (int) ; 
 int /*<<< orphan*/  tcgetattr (int,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int,int /*<<< orphan*/ ,struct termios*) ; 

char *getpass(const char *prompt)
{
	int fd;
	struct termios s, t;
	ssize_t l;
	static char password[128];

	if ((fd = open("/dev/tty", O_RDWR|O_NOCTTY|O_CLOEXEC)) < 0) return 0;

	tcgetattr(fd, &t);
	s = t;
	t.c_lflag &= ~(ECHO|ISIG);
	t.c_lflag |= ICANON;
	t.c_iflag &= ~(INLCR|IGNCR);
	t.c_iflag |= ICRNL;
	tcsetattr(fd, TCSAFLUSH, &t);
	tcdrain(fd);

	dprintf(fd, "%s", prompt);

	l = read(fd, password, sizeof password);
	if (l >= 0) {
		if (l > 0 && password[l-1] == '\n') l--;
		password[l] = 0;
	}

	tcsetattr(fd, TCSAFLUSH, &s);

	dprintf(fd, "\n");
	close(fd);

	return l<0 ? 0 : password;
}