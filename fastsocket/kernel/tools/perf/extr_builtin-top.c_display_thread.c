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
struct termios {int c_lflag; scalar_t__* c_cc; } ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct perf_top {int delay_secs; } ;

/* Variables and functions */
 int ECHO ; 
 int /*<<< orphan*/  EINTR ; 
 int ICANON ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  TCSAFLUSH ; 
 int /*<<< orphan*/  TCSANOW ; 
 size_t VMIN ; 
 size_t VTIME ; 
 int /*<<< orphan*/  errno ; 
 int getc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perf_top__handle_keypress (struct perf_top*,int) ; 
 int /*<<< orphan*/  perf_top__print_sym_table (struct perf_top*) ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  pthread__unblock_sigwinch () ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  tcgetattr (int /*<<< orphan*/ ,struct termios*) ; 
 int /*<<< orphan*/  tcsetattr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct termios*) ; 

__attribute__((used)) static void *display_thread(void *arg)
{
	struct pollfd stdin_poll = { .fd = 0, .events = POLLIN };
	struct termios tc, save;
	struct perf_top *top = arg;
	int delay_msecs, c;

	tcgetattr(0, &save);
	tc = save;
	tc.c_lflag &= ~(ICANON | ECHO);
	tc.c_cc[VMIN] = 0;
	tc.c_cc[VTIME] = 0;

	pthread__unblock_sigwinch();
repeat:
	delay_msecs = top->delay_secs * 1000;
	tcsetattr(0, TCSANOW, &tc);
	/* trash return*/
	getc(stdin);

	while (1) {
		perf_top__print_sym_table(top);
		/*
		 * Either timeout expired or we got an EINTR due to SIGWINCH,
		 * refresh screen in both cases.
		 */
		switch (poll(&stdin_poll, 1, delay_msecs)) {
		case 0:
			continue;
		case -1:
			if (errno == EINTR)
				continue;
			/* Fall trhu */
		default:
			goto process_hotkey;
		}
	}
process_hotkey:
	c = getc(stdin);
	tcsetattr(0, TCSAFLUSH, &save);

	perf_top__handle_keypress(top, c);
	goto repeat;

	return NULL;
}