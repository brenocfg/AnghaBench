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

void
cttest_stats_tube()
{
    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "use tubea\r\n");
    ckresp(fd, "USING tubea\r\n");
    mustsend(fd, "put 0 0 0 1\r\n");
    mustsend(fd, "x\r\n");
    ckresp(fd, "INSERTED 1\r\n");
    mustsend(fd, "delete 1\r\n");
    ckresp(fd, "DELETED\r\n");

    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\nname: tubea\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-urgent: 0\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-ready: 0\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-reserved: 0\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-delayed: 0\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-buried: 0\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ntotal-jobs: 1\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-using: 1\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-watching: 0\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-waiting: 0\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncmd-delete: 1\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncmd-pause-tube: 0\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\npause: 0\n");
    mustsend(fd, "stats-tube tubea\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\npause-time-left: 0\n");

    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\nname: default\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-urgent: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-ready: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-reserved: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-delayed: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-jobs-buried: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ntotal-jobs: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-using: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-watching: 1\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncurrent-waiting: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncmd-delete: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\ncmd-pause-tube: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\npause: 0\n");
    mustsend(fd, "stats-tube default\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\npause-time-left: 0\n");
}