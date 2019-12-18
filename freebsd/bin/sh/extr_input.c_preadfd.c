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
struct TYPE_2__ {scalar_t__ fd; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int BUFSIZ ; 
 scalar_t__ EINTR ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 scalar_t__ el ; 
 char* el_gets (scalar_t__,int*) ; 
 int /*<<< orphan*/  el_resize (scalar_t__) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  out2fmt_flush (char*) ; 
 TYPE_1__* parsefile ; 
 int /*<<< orphan*/  parsenextc ; 
 int read (scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
preadfd(void)
{
	int nr;
	parsenextc = parsefile->buf;

retry:
#ifndef NO_HISTORY
	if (parsefile->fd == 0 && el) {
		static const char *rl_cp;
		static int el_len;

		if (rl_cp == NULL) {
			el_resize(el);
			rl_cp = el_gets(el, &el_len);
		}
		if (rl_cp == NULL)
			nr = el_len == 0 ? 0 : -1;
		else {
			nr = el_len;
			if (nr > BUFSIZ)
				nr = BUFSIZ;
			memcpy(parsefile->buf, rl_cp, nr);
			if (nr != el_len) {
				el_len -= nr;
				rl_cp += nr;
			} else
				rl_cp = NULL;
		}
	} else
#endif
		nr = read(parsefile->fd, parsefile->buf, BUFSIZ);

	if (nr <= 0) {
                if (nr < 0) {
                        if (errno == EINTR)
                                goto retry;
                        if (parsefile->fd == 0 && errno == EWOULDBLOCK) {
                                int flags = fcntl(0, F_GETFL, 0);
                                if (flags >= 0 && flags & O_NONBLOCK) {
                                        flags &=~ O_NONBLOCK;
                                        if (fcntl(0, F_SETFL, flags) >= 0) {
						out2fmt_flush("sh: turning off NDELAY mode\n");
                                                goto retry;
                                        }
                                }
                        }
                }
                nr = -1;
	}
	return nr;
}