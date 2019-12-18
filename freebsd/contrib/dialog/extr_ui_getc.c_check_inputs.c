#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timeval {int tv_usec; scalar_t__ tv_sec; } ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_4__ {TYPE_1__* getc_callbacks; } ;
struct TYPE_3__ {scalar_t__ input; int /*<<< orphan*/  input_ready; struct TYPE_3__* next; } ;
typedef  TYPE_1__ DIALOG_CALLBACK ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int WTIMEOUT_VAL ; 
 TYPE_2__ dialog_state ; 
 int fileno (scalar_t__) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timeval*) ; 

__attribute__((used)) static int
check_inputs(void)
{
    DIALOG_CALLBACK *p;
    fd_set read_fds;
    struct timeval test;
    int last_fd = -1;
    int fd;
    int found;
    int result = -1;

    if ((p = dialog_state.getc_callbacks) != 0) {
	FD_ZERO(&read_fds);

	while (p != 0) {
	    p->input_ready = FALSE;
	    if (p->input != 0 && (fd = fileno(p->input)) >= 0) {
		FD_SET(fd, &read_fds);
		if (last_fd < fd)
		    last_fd = fd;
	    }
	    p = p->next;
	}

	test.tv_sec = 0;
	test.tv_usec = WTIMEOUT_VAL * 1000;
	found = select(last_fd + 1, &read_fds,
		       (fd_set *) 0,
		       (fd_set *) 0,
		       &test);

	if (found > 0) {
	    for (p = dialog_state.getc_callbacks; p != 0; p = p->next) {
		if (p->input != 0
		    && (fd = fileno(p->input)) >= 0
		    && FD_ISSET(fd, &read_fds)) {
		    p->input_ready = TRUE;
		    result = fd;
		}
	    }
	}
    }

    return result;
}