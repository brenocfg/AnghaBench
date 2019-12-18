#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_port; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  socklen_t ;
typedef  int /*<<< orphan*/  addr ;
struct TYPE_5__ {int fd; } ;
struct TYPE_6__ {TYPE_1__ sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int getsockname (int,struct sockaddr*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kill_srvpid ; 
 int make_server_socket (char*,char*) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  prot_init () ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  set_sig_handler () ; 
 TYPE_2__ srv ; 
 int /*<<< orphan*/  srv_acquire_wal (TYPE_2__*) ; 
 scalar_t__ srvpid ; 
 int /*<<< orphan*/  srvserve (TYPE_2__*) ; 
 int /*<<< orphan*/  twarn (char*) ; 

__attribute__((used)) static int
mustforksrv(void)
{
    struct sockaddr_in addr;

    srv.sock.fd = make_server_socket("127.0.0.1", "0");
    if (srv.sock.fd == -1) {
        puts("mustforksrv failed");
        exit(1);
    }

    size_t len = sizeof(addr);
    int r = getsockname(srv.sock.fd, (struct sockaddr *)&addr, (socklen_t *)&len);
    if (r == -1 || len > sizeof(addr)) {
        puts("mustforksrv failed");
        exit(1);
    }

    int port = ntohs(addr.sin_port);
    srvpid = fork();
    if (srvpid < 0) {
        twarn("fork");
        exit(1);
    }

    if (srvpid > 0) {
        // On exit the parent (test) sends SIGTERM to the child.
        atexit(kill_srvpid);
        printf("start server port=%d pid=%d\n", port, srvpid);
        return port;
    }

    /* now in child */

    set_sig_handler();
    prot_init();

    srv_acquire_wal(&srv);

    srvserve(&srv); /* does not return */
    exit(1); /* satisfy the compiler */
}