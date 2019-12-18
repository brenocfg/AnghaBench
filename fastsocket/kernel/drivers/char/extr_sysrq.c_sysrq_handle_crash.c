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
 int panic_on_oops ; 
 int /*<<< orphan*/  wmb () ; 

__attribute__((used)) static void sysrq_handle_crash(int key, struct tty_struct *tty)
{
	char *killer = NULL;

	panic_on_oops = 1;	/* force panic */
	wmb();
	*killer = 1;
}