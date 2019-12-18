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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  name ;
struct TYPE_5__ {int fd; } ;
struct TYPE_6__ {TYPE_1__ sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 char* ctdir () ; 
 int /*<<< orphan*/  exist (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  kill_srvpid ; 
 int make_server_socket (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  prot_init () ; 
 int /*<<< orphan*/  puts (char*) ; 
 int /*<<< orphan*/  set_sig_handler () ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 TYPE_2__ srv ; 
 int /*<<< orphan*/  srv_acquire_wal (TYPE_2__*) ; 
 scalar_t__ srvpid ; 
 int /*<<< orphan*/  srvserve (TYPE_2__*) ; 
 int /*<<< orphan*/  twarn (char*) ; 

__attribute__((used)) static char *
mustforksrv_unix(void)
{
    static char path[90];
    char name[95];
    snprintf(path, sizeof(path), "%s/socket", ctdir());
    snprintf(name, sizeof(name), "unix:%s", path);
    srv.sock.fd = make_server_socket(name, NULL);
    if (srv.sock.fd == -1) {
        puts("mustforksrv_unix failed");
        exit(1);
    }

    srvpid = fork();
    if (srvpid < 0) {
        twarn("fork");
        exit(1);
    }

    if (srvpid > 0) {
        // On exit the parent (test) sends SIGTERM to the child.
        atexit(kill_srvpid);
        printf("start server socket=%s\n", path);
        assert(exist(path));
        return path;
    }

    /* now in child */

    set_sig_handler();
    prot_init();

    srv_acquire_wal(&srv);

    srvserve(&srv); /* does not return */
    exit(1); /* satisfy the compiler */
}