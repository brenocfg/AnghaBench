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
cttest_reserve_job_ttr_deadline_soon()
{
    int port = SERVER();
    int fd = mustdiallocal(port);

    mustsend(fd, "put 0 5 1 1\r\n");
    mustsend(fd, "a\r\n");
    ckresp(fd, "INSERTED 1\r\n");

    mustsend(fd, "stats-job 1\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\nstate: delayed\n");

    mustsend(fd, "reserve-job 1\r\n");
    ckresp(fd, "RESERVED 1 1\r\n");
    ckresp(fd, "a\r\n");

    // After 0.1s the job should be still reserved.
    usleep(100000);
    mustsend(fd, "stats-job 1\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\nstate: reserved\n");

    // Reservation made with reserve-job should behave the same way as other
    // reserve commands, e.g. produce "deadline soon" message, and get released
    // when ttr ends.
    mustsend(fd, "reserve-with-timeout 1\r\n");
    ckresp(fd, "DEADLINE_SOON\r\n");

    // Job should be reserved; last "reserve" took less than 1s.
    mustsend(fd, "stats-job 1\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\nstate: reserved\n");

    // We are not able to process the job in time. Check that it gets released.
    // The job was in delayed state. It becomes ready when it gets auto-released.
    usleep(1000000); // 1.0s
    // put a dummy job
    mustsend(fd, "put 0 0 1 1\r\n");
    mustsend(fd, "B\r\n");
    ckresp(fd, "INSERTED 2\r\n");
    // check that ID=1 gets released
    mustsend(fd, "stats-job 1\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\nstate: ready\n");
}