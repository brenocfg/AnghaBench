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
 int linux_stdin_claimed ; 

void linux_terminal_claim_stdin(void)
{
   /* We need to disable use of stdin command interface if
    * stdin is supposed to be used for input. */
   linux_stdin_claimed = true;
}