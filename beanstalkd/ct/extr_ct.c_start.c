#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int fd; scalar_t__ pid; int /*<<< orphan*/  (* f ) () ;int /*<<< orphan*/  dir; } ;
typedef  TYPE_1__ Test ;

/* Variables and functions */
 int /*<<< orphan*/  TmpDirPat ; 
 int close (int) ; 
 int /*<<< orphan*/  ctfailnow () ; 
 int /*<<< orphan*/  curdir ; 
 int /*<<< orphan*/  die (int,int /*<<< orphan*/ ,char*) ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fail ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/ * mkdtemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpgid (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 () ; 
 int tmpfd () ; 

__attribute__((used)) static void
start(Test *t)
{
    t->fd = tmpfd();
    strcpy(t->dir, TmpDirPat);
    if (mkdtemp(t->dir) == NULL) {
	die(1, errno, "mkdtemp");
    }
    fflush(NULL);
    t->pid = fork();
    if (t->pid < 0) {
        die(1, errno, "fork");
    } else if (!t->pid) {
        setpgid(0, 0);
        if (dup2(t->fd, 1) == -1) {
            die(3, errno, "dup2");
        }
        if (close(t->fd) == -1) {
            die(3, errno, "fclose");
        }
        if (dup2(1, 2) == -1) {
            die(3, errno, "dup2");
        }
        curdir = t->dir;
        t->f();
        if (fail) {
            ctfailnow();
        }
        exit(0);
    }
    setpgid(t->pid, t->pid);
}