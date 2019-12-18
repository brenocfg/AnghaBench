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
 int /*<<< orphan*/  close (int) ; 
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 

void
cttest_close_releases_job()
{
    int port = SERVER();
    int cons = mustdiallocal(port);
    int prod = mustdiallocal(port);
    mustsend(cons, "reserve-with-timeout 1\r\n");

    mustsend(prod, "put 0 0 100 1\r\n");
    mustsend(prod, "a\r\n");
    ckresp(prod, "INSERTED 1\r\n");

    ckresp(cons, "RESERVED 1 1\r\n");
    ckresp(cons, "a\r\n");

    mustsend(prod, "stats-job 1\r\n");
    ckrespsub(prod, "OK ");
    ckrespsub(prod, "\nstate: reserved\n");

    // Closed consumer connection should make the job ready sooner than ttr=100.
    close(cons);

    // Job should be released in less than 1s. It is not instantly;
    // we do not make guarantees about how soon jobs should be released.
    mustsend(prod, "reserve-with-timeout 1\r\n");
    ckresp(prod, "RESERVED 1 1\r\n");
    ckresp(prod, "a\r\n");
}