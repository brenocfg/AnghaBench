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
cttest_statsjob_ck_format()
{
    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "stats-job 111ABC\r\n");
    ckresp(fd, "BAD_FORMAT\r\n");
    mustsend(fd, "stats-job 111 222\r\n");
    ckresp(fd, "BAD_FORMAT\r\n");
    mustsend(fd, "stats-job 111\r\n");
    ckresp(fd, "NOT_FOUND\r\n");
}