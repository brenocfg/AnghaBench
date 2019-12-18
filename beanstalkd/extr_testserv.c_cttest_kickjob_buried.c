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
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 

void
cttest_kickjob_buried()
{
    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "put 0 0 1 1\r\n");
    mustsend(fd, "A\r\n");
    ckresp(fd, "INSERTED 1\r\n");

    mustsend(fd, "reserve\r\n");
    ckresp(fd, "RESERVED 1 1\r\n");
    ckresp(fd, "A\r\n");
    mustsend(fd, "bury 1 0\r\n");
    ckresp(fd, "BURIED\r\n");

    mustsend(fd, "kick-job 100\r\n");
    ckresp(fd, "NOT_FOUND\r\n");
    mustsend(fd, "kick-job 1\r\n");
    ckresp(fd, "KICKED\r\n");
    mustsend(fd, "kick-job 1\r\n");
    ckresp(fd, "NOT_FOUND\r\n");
}