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
 int timeout ; 

void
cttest_reserve_with_timeout_2conns()
{
    int fd0, fd1;

    job_data_size_limit = 10;

    int port = SERVER();
    fd0 = mustdiallocal(port);
    fd1 = mustdiallocal(port);
    mustsend(fd0, "watch foo\r\n");
    ckresp(fd0, "WATCHING 2\r\n");
    mustsend(fd0, "reserve-with-timeout 1\r\n");
    mustsend(fd1, "watch foo\r\n");
    ckresp(fd1, "WATCHING 2\r\n");
    timeout = 1100000000; // 1.1s
    ckresp(fd0, "TIMED_OUT\r\n");
}