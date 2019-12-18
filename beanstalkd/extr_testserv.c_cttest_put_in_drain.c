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
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  ckresp (int,char*) ; 
 int /*<<< orphan*/  enter_drain_mode (int /*<<< orphan*/ ) ; 
 int mustdiallocal (int) ; 
 int /*<<< orphan*/  mustsend (int,char*) ; 

void
cttest_put_in_drain()
{
    enter_drain_mode(SIGUSR1);
    int port = SERVER();
    int fd = mustdiallocal(port);
    mustsend(fd, "put 0 0 1 1\r\n");
    mustsend(fd, "x\r\n");
    ckresp(fd, "DRAINING\r\n");
}