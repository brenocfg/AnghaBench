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
 int /*<<< orphan*/  close (int) ; 
 int fd_serv ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sleep (int) ; 

__attribute__((used)) static void teardown_connection(void)
{
#ifdef DEBUG
    printf("[main] Tearing down connection to CNC!\n");
#endif

    if (fd_serv != -1)
        close(fd_serv);
    fd_serv = -1;
    sleep(1);
}