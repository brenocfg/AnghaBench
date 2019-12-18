#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int dummy; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
struct TYPE_5__ {int fd; scalar_t__ f; TYPE_1__* x; } ;
struct TYPE_4__ {TYPE_2__ sock; int /*<<< orphan*/ * srv; } ;
typedef  int /*<<< orphan*/  Server ;
typedef  scalar_t__ Handle ;
typedef  TYPE_1__ Conn ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EWOULDBLOCK ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int /*<<< orphan*/  STATE_WANT_COMMAND ; 
 int /*<<< orphan*/  UNUSED_PARAMETER (short const) ; 
 int accept (int const,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  default_tube ; 
 int /*<<< orphan*/  epollq_apply () ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* make_conn (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ prothandle ; 
 int sockwant (TYPE_2__*,char) ; 
 int /*<<< orphan*/  twarn (char*) ; 
 int /*<<< orphan*/  twarnx (char*) ; 
 scalar_t__ verbose ; 

void
h_accept(const int fd, const short which, Server *s)
{
    UNUSED_PARAMETER(which);
    struct sockaddr_storage addr;

    socklen_t addrlen = sizeof addr;
    int cfd = accept(fd, (struct sockaddr *)&addr, &addrlen);
    if (cfd == -1) {
        if (errno != EAGAIN && errno != EWOULDBLOCK) twarn("accept()");
        epollq_apply();
        return;
    }
    if (verbose) {
        printf("accept %d\n", cfd);
    }

    int flags = fcntl(cfd, F_GETFL, 0);
    if (flags < 0) {
        twarn("getting flags");
        close(cfd);
        if (verbose) {
            printf("close %d\n", cfd);
        }
        epollq_apply();
        return;
    }

    int r = fcntl(cfd, F_SETFL, flags | O_NONBLOCK);
    if (r < 0) {
        twarn("setting O_NONBLOCK");
        close(cfd);
        if (verbose) {
            printf("close %d\n", cfd);
        }
        epollq_apply();
        return;
    }

    Conn *c = make_conn(cfd, STATE_WANT_COMMAND, default_tube, default_tube);
    if (!c) {
        twarnx("make_conn() failed");
        close(cfd);
        if (verbose) {
            printf("close %d\n", cfd);
        }
        epollq_apply();
        return;
    }
    c->srv = s;
    c->sock.x = c;
    c->sock.f = (Handle)prothandle;
    c->sock.fd = cfd;

    r = sockwant(&c->sock, 'r');
    if (r == -1) {
        twarn("sockwant");
        close(cfd);
        if (verbose) {
            printf("close %d\n", cfd);
        }
    }
    epollq_apply();
}