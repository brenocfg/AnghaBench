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
 int job_data_size_limit ; 
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 

void
cttest_too_big()
{
    job_data_size_limit = 10;
    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "put 0 0 0 11\r\n");
    mustsend(fd, "delete 9999\r\n");
    mustsend(fd, "put 0 0 0 1\r\n");
    mustsend(fd, "x\r\n");
    ckresp(fd, "JOB_TOO_BIG\r\n");
    ckresp(fd, "INSERTED 1\r\n");
}