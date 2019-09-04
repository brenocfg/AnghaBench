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
struct TYPE_2__ {scalar_t__ verbose; } ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  chdir (char*) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dup (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal (char*) ; 
 int fork () ; 
 int getdtablesize () ; 
 int /*<<< orphan*/  getgid () ; 
 int /*<<< orphan*/  getuid () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  setgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsid () ; 
 TYPE_1__ settings ; 
 int /*<<< orphan*/  setuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler ; 
 int /*<<< orphan*/  umask (int /*<<< orphan*/ ) ; 

void daemonize(int keepfd) {
    int pid, i;

    umask(0);
    chdir("/");
    setgid(getgid());
    setuid(getuid());

    /* Double fork to daemonize */
    pid = fork();
    if (pid<0) { fatal("fork error"); }
    if (pid>0) { exit(0); }  // parent exits
    setsid();                // Obtain new process group
    pid = fork();
    if (pid<0) { fatal("fork error"); }
    if (pid>0) { exit(0); }  // parent exits

    /* Signal handling */
    signal(SIGHUP, signal_handler);   // catch HUP
    signal(SIGTERM, signal_handler);  // catch kill

    /* Close open files */
    for (i=getdtablesize(); i>=0; --i) {
        if (i != keepfd) {
            close(i);
        } else if (settings.verbose) {
            printf("keeping fd %d\n", keepfd);
        }
    }
    i=open("/dev/null", O_RDWR);  // Redirect stdin
    dup(i);                       // Redirect stdout
    dup(i);                       // Redirect stderr
}