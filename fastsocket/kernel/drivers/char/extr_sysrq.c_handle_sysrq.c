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
 int /*<<< orphan*/  __handle_sysrq (int,struct tty_struct*,int) ; 
 scalar_t__ sysrq_on () ; 

void handle_sysrq(int key, struct tty_struct *tty)
{
	if (sysrq_on())
		__handle_sysrq(key, tty, 1);
}