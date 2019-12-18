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
struct tty_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGKILL ; 
 int console_loglevel ; 
 int /*<<< orphan*/  send_sig_all (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sysrq_handle_kill(int key, struct tty_struct *tty)
{
	send_sig_all(SIGKILL);
	console_loglevel = 8;
}