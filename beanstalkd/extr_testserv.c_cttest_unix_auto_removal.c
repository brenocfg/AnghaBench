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
 int /*<<< orphan*/  SERVER_UNIX () ; 
 int /*<<< orphan*/  kill_srvpid () ; 

void
cttest_unix_auto_removal()
{
    // Twice, to trigger autoremoval
    SERVER_UNIX();
    kill_srvpid();
    SERVER_UNIX();
}