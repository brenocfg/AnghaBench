#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_11__ {int /*<<< orphan*/  fd; scalar_t__ f; TYPE_3__* x; } ;
struct TYPE_8__ {int /*<<< orphan*/  setpos; int /*<<< orphan*/  less; } ;
struct TYPE_10__ {TYPE_5__ sock; TYPE_1__ conns; } ;
struct TYPE_9__ {int /*<<< orphan*/  x; int /*<<< orphan*/  (* f ) (int /*<<< orphan*/ ,int) ;} ;
typedef  TYPE_2__ Socket ;
typedef  TYPE_3__ Server ;
typedef  scalar_t__ Handle ;

/* Variables and functions */
 int /*<<< orphan*/  conn_less ; 
 int /*<<< orphan*/  conn_setpos ; 
 int /*<<< orphan*/  exit (int) ; 
 int listen (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  prottick (TYPE_3__*) ; 
 int sockinit () ; 
 int socknext (TYPE_2__**,int /*<<< orphan*/ ) ; 
 int sockwant (TYPE_5__*,char) ; 
 scalar_t__ srvaccept ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  twarn (char*) ; 
 int /*<<< orphan*/  twarnx (char*) ; 

void
srvserve(Server *s)
{
    int r;
    Socket *sock;

    if (sockinit() == -1) {
        twarnx("sockinit");
        exit(1);
    }

    s->sock.x = s;
    s->sock.f = (Handle)srvaccept;
    s->conns.less = conn_less;
    s->conns.setpos = conn_setpos;

    r = listen(s->sock.fd, 1024);
    if (r == -1) {
        twarn("listen");
        return;
    }

    r = sockwant(&s->sock, 'r');
    if (r == -1) {
        twarn("sockwant");
        exit(2);
    }


    for (;;) {
        int64 period = prottick(s);

        int rw = socknext(&sock, period);
        if (rw == -1) {
            twarnx("socknext");
            exit(1);
        }

        if (rw) {
            sock->f(sock->x, rw);
        }
    }
}