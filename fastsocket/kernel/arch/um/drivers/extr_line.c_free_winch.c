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
struct winch {int pid; int fd; scalar_t__ stack; int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINCH_IRQ ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct winch*) ; 
 int /*<<< orphan*/  free_stack (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct winch*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  os_close_file (int) ; 
 int /*<<< orphan*/  os_kill_process (int,int) ; 

__attribute__((used)) static void free_winch(struct winch *winch, int free_irq_ok)
{
	list_del(&winch->list);

	if (winch->pid != -1)
		os_kill_process(winch->pid, 1);
	if (winch->fd != -1)
		os_close_file(winch->fd);
	if (winch->stack != 0)
		free_stack(winch->stack, 0);
	if (free_irq_ok)
		free_irq(WINCH_IRQ, winch);
	kfree(winch);
}