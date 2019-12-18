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
typedef  int int64 ;

/* Variables and functions */
 int SERVER () ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ckresp (int,char*) ; 
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 
 int nanoseconds () ; 

void
cttest_pause()
{
    int64 s;

    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "put 0 0 0 1\r\n");
    mustsend(fd, "x\r\n");
    ckresp(fd, "INSERTED 1\r\n");
    s = nanoseconds();
    mustsend(fd, "pause-tube default 1\r\n");
    ckresp(fd, "PAUSED\r\n");
    mustsend(fd, "reserve\r\n");
    ckresp(fd, "RESERVED 1 1\r\n");
    ckresp(fd, "x\r\n");
    assert(nanoseconds() - s >= 1000000000); // 1s
}