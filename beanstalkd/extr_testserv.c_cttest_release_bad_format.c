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
cttest_release_bad_format()
{
    int port = SERVER();
    int fd = mustdiallocal(port);

    // bad id
    mustsend(fd, "release 18446744073709551616 1 1\r\n"); // UINT64_MAX+1
    ckresp(fd, "BAD_FORMAT\r\n");
    mustsend(fd, "release 184467440737095516160000000000000000000000000000 1 1\r\n");
    ckresp(fd, "BAD_FORMAT\r\n");
    mustsend(fd, "release foo111\r\n");
    ckresp(fd, "BAD_FORMAT\r\n");
    mustsend(fd, "release 111foo\r\n");
    ckresp(fd, "BAD_FORMAT\r\n");

    // bad priority
    mustsend(fd, "release 18446744073709551615 abc 1\r\n");
    ckresp(fd, "BAD_FORMAT\r\n");

    // bad duration
    mustsend(fd, "release 18446744073709551615 1 abc\r\n");
    ckresp(fd, "BAD_FORMAT\r\n");
}