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
 char* SERVER_UNIX () ; 
 int /*<<< orphan*/  ckresp (int,char*) ; 
 int mustdialunix (char*) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

void
cttest_peek_ok_unix()
{
    char *name = SERVER_UNIX();
    int fd = mustdialunix(name);
    mustsend(fd, "put 0 0 1 1\r\n");
    mustsend(fd, "a\r\n");
    ckresp(fd, "INSERTED 1\r\n");

    mustsend(fd, "peek 1\r\n");
    ckresp(fd, "FOUND 1 1\r\n");
    ckresp(fd, "a\r\n");

    unlink(name);
}