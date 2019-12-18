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
cttest_reserve_job_delayed()
{
    int port = SERVER();
    int fd = mustdiallocal(port);

    mustsend(fd, "put 0 100 1 1\r\n");
    mustsend(fd, "A\r\n");
    ckresp(fd, "INSERTED 1\r\n");
    mustsend(fd, "put 0 100 1 1\r\n");
    mustsend(fd, "B\r\n");
    ckresp(fd, "INSERTED 2\r\n");
    mustsend(fd, "put 0 100 1 1\r\n");
    mustsend(fd, "C\r\n");
    ckresp(fd, "INSERTED 3\r\n");

    mustsend(fd, "reserve-job 2\r\n");
    ckresp(fd, "RESERVED 2 1\r\n");
    ckresp(fd, "B\r\n");

    mustsend(fd, "release 2 1 0\r\n");
    ckresp(fd, "RELEASED\r\n");

    // verify that job was released in ready state.
    mustsend(fd, "stats-job 2\r\n");
    ckrespsub(fd, "OK ");
    ckrespsub(fd, "\nstate: ready\n");
}