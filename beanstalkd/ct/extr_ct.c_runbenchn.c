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
struct TYPE_3__ {int status; int /*<<< orphan*/  bytes; int /*<<< orphan*/  dur; int /*<<< orphan*/  dir; int /*<<< orphan*/  (* f ) (int) ;} ;
typedef  TYPE_1__ Benchmark ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  TmpDirPat ; 
 int /*<<< orphan*/  bbytes ; 
 int /*<<< orphan*/  bdur ; 
 int close (int) ; 
 int /*<<< orphan*/  copyfd (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ctstarttimer () ; 
 int /*<<< orphan*/  ctstoptimer () ; 
 int /*<<< orphan*/  curdir ; 
 int /*<<< orphan*/  die (int,int /*<<< orphan*/ ,char*) ; 
 int dup2 (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ *) ; 
 int fork () ; 
 int /*<<< orphan*/  killpg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lseek (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mkdtemp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rmtree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setpgid (int,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int) ; 
 int tmpfd () ; 
 int waitpid (int,int*,int /*<<< orphan*/ ) ; 
 int write (int,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
runbenchn(Benchmark *b, int n)
{
    int outfd = tmpfd();
    int durfd = tmpfd();
    strcpy(b->dir, TmpDirPat);
    if (mkdtemp(b->dir) == NULL) {
	die(1, errno, "mkdtemp");
    }
    fflush(NULL);
    int pid = fork();
    if (pid < 0) {
        die(1, errno, "fork");
    } else if (!pid) {
        setpgid(0, 0);
        if (dup2(outfd, 1) == -1) {
            die(3, errno, "dup2");
        }
        if (close(outfd) == -1) {
            die(3, errno, "fclose");
        }
        if (dup2(1, 2) == -1) {
            die(3, errno, "dup2");
        }
        curdir = b->dir;
        ctstarttimer();
        b->f(n);
        ctstoptimer();
        if (write(durfd, &bdur, sizeof bdur) != sizeof bdur) {
            die(3, errno, "write");
        }
        if (write(durfd, &bbytes, sizeof bbytes) != sizeof bbytes) {
            die(3, errno, "write");
        }
        exit(0);
    }
    setpgid(pid, pid);

    pid = waitpid(pid, &b->status, 0);
    if (pid == -1) {
        die(3, errno, "wait");
    }
    killpg(pid, SIGKILL);
    rmtree(b->dir);
    if (b->status != 0) {
        putchar('\n');
        lseek(outfd, 0, SEEK_SET);
        copyfd(stdout, outfd);
        return;
    }

    lseek(durfd, 0, SEEK_SET);
    int r = read(durfd, &b->dur, sizeof b->dur);
    if (r != sizeof b->dur) {
        perror("read");
        b->status = 1;
    }
    r = read(durfd, &b->bytes, sizeof b->bytes);
    if (r != sizeof b->bytes) {
        perror("read");
        b->status = 1;
    }
}