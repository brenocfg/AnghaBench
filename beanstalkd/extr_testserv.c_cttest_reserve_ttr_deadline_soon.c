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
cttest_reserve_ttr_deadline_soon()
{
    int port = SERVER();
    int fd = mustdiallocal(port);

    mustsend(fd, "put 0 0 1 1\r\n");
    mustsend(fd, "a\r\n");
    ckresp(fd, "INSERTED 1\r\n");

    mustsend(fd, "reserve-with-timeout 1\r\n");
    ckresp(fd, "RESERVED 1 1\r\n");
    ckresp(fd, "a\r\n");

    // After 0.2s the job should be still reserved.
    usleep(200000);
    mustsend(fd, "stats-job 1\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\nstate: reserved\n");

    mustsend(fd, "reserve-with-timeout 1\r\n");
    ckresp(fd, "DEADLINE_SOON\r\n");

    // Job should be reserved; last "reserve" took less than 1s.
    mustsend(fd, "stats-job 1\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\nstate: reserved\n");

    // We don't want to process the job, so release it and check that it's ready.
    mustsend(fd, "release 1 0 0\r\n");
    ckresp(fd, "RELEASED\r\n");
    mustsend(fd, "stats-job 1\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\nstate: ready\n");
}