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
cttest_multi_tube()
{
    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "use abc\r\n");
    ckresp(fd, "USING abc\r\n");
    mustsend(fd, "put 999999 0 0 0\r\n");
    mustsend(fd, "\r\n");
    ckresp(fd, "INSERTED 1\r\n");
    mustsend(fd, "use def\r\n");
    ckresp(fd, "USING def\r\n");
    mustsend(fd, "put 99 0 0 0\r\n");
    mustsend(fd, "\r\n");
    ckresp(fd, "INSERTED 2\r\n");
    mustsend(fd, "watch abc\r\n");
    ckresp(fd, "WATCHING 2\r\n");
    mustsend(fd, "watch def\r\n");
    ckresp(fd, "WATCHING 3\r\n");
    mustsend(fd, "reserve\r\n");
    ckresp(fd, "RESERVED 2 0\r\n");
}