#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int SERVER () ; 
 int /*<<< orphan*/  ckresp (int,char*) ; 
 int /*<<< orphan*/  ckrespsub (int,char*) ; 
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 
 int /*<<< orphan*/  usleep (int) ; 

void
cttest_delayed_to_ready()
{
    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "put 0 1 1 0\r\n");
    mustsend(fd, "\r\n");
    ckresp(fd, "INSERTED 1\r\n");

    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-ready: 0\n");

    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-delayed: 1\n");

    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ntotal-jobs: 1\n");

    usleep(1010000); // 1.01 sec

    // check that after 1 sec the delayed job is ready again

    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-ready: 1\n");

    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-delayed: 0\n");

    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ntotal-jobs: 1\n");
}