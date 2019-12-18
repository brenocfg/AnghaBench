#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int const fd; } ;
struct TYPE_11__ {int halfclosed; scalar_t__ state; int /*<<< orphan*/  cmd_read; int /*<<< orphan*/  cmd; int /*<<< orphan*/  cmd_len; TYPE_1__ sock; } ;
typedef  TYPE_2__ Conn ;

/* Variables and functions */
 scalar_t__ STATE_CLOSE ; 
 int /*<<< orphan*/  close (int const) ; 
 scalar_t__ cmd_data_ready (TYPE_2__*) ; 
 int /*<<< orphan*/  conn_process_io (TYPE_2__*) ; 
 int /*<<< orphan*/  connclose (TYPE_2__*) ; 
 int /*<<< orphan*/  dispatch_cmd (TYPE_2__*) ; 
 int /*<<< orphan*/  epollq_apply () ; 
 int /*<<< orphan*/  epollq_rmconn (TYPE_2__*) ; 
 int /*<<< orphan*/  fill_extra_data (TYPE_2__*) ; 
 int /*<<< orphan*/  scan_line_end (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twarnx (char*) ; 

__attribute__((used)) static void
h_conn(const int fd, const short which, Conn *c)
{
    if (fd != c->sock.fd) {
        twarnx("Argh! event fd doesn't match conn fd.");
        close(fd);
        connclose(c);
        epollq_apply();
        return;
    }

    if (which == 'h') {
        c->halfclosed = 1;
    }

    conn_process_io(c);
    while (cmd_data_ready(c) && (c->cmd_len = scan_line_end(c->cmd, c->cmd_read))) {
        dispatch_cmd(c);
        fill_extra_data(c);
    }
    if (c->state == STATE_CLOSE) {
        epollq_rmconn(c);
        connclose(c);
    }
    epollq_apply();
}