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
cttest_peek_not_found()
{
    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "put 0 0 1 1\r\n");
    mustsend(fd, "a\r\n");
    ckresp(fd, "INSERTED 1\r\n");

    mustsend(fd, "peek 2\r\n");
    ckresp(fd, "NOT_FOUND\r\n");
    mustsend(fd, "peek 18446744073709551615\r\n");  // UINT64_MAX
    ckresp(fd, "NOT_FOUND\r\n");
}