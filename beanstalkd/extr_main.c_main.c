#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int fd; } ;
struct TYPE_7__ {scalar_t__ user; TYPE_1__ sock; int /*<<< orphan*/  port; int /*<<< orphan*/  addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  UNUSED_PARAMETER (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getpid () ; 
 int make_server_socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optparse (TYPE_2__*,char**) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 char* progname ; 
 int /*<<< orphan*/  prot_init () ; 
 int /*<<< orphan*/  set_sig_handlers () ; 
 int /*<<< orphan*/  setlinebuf (int /*<<< orphan*/ ) ; 
 TYPE_2__ srv ; 
 int /*<<< orphan*/  srv_acquire_wal (TYPE_2__*) ; 
 int /*<<< orphan*/  srvserve (TYPE_2__*) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  su (scalar_t__) ; 
 int /*<<< orphan*/  twarnx (char*) ; 
 scalar_t__ verbose ; 

int
main(int argc, char **argv)
{
    UNUSED_PARAMETER(argc);

    progname = argv[0];
    setlinebuf(stdout);
    optparse(&srv, argv+1);

    if (verbose) {
        printf("pid %d\n", getpid());
    }

    int r = make_server_socket(srv.addr, srv.port);
    if (r == -1) {
        twarnx("make_server_socket()");
        exit(111);
    }

    srv.sock.fd = r;

    prot_init();

    if (srv.user)
        su(srv.user);
    set_sig_handlers();

    srv_acquire_wal(&srv);
    srvserve(&srv);
    exit(0);
}