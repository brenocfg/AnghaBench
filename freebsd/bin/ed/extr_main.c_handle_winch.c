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
struct winsize {int ws_row; int ws_col; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIOCGWINSZ ; 
 int cols ; 
 int errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int rows ; 
 int sigflags ; 

void
handle_winch(int signo)
{
	int save_errno = errno;

	struct winsize ws;		/* window size structure */

	sigflags &= ~(1 << (signo - 1));
	if (ioctl(0, TIOCGWINSZ, (char *) &ws) >= 0) {
		if (ws.ws_row > 2) rows = ws.ws_row - 2;
		if (ws.ws_col > 8) cols = ws.ws_col - 8;
	}
	errno = save_errno;
}