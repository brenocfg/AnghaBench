#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct signal_struct {int /*<<< orphan*/ * tty_audit_buf; int /*<<< orphan*/  audit_tty_log_passwd; int /*<<< orphan*/  audit_tty; } ;
struct TYPE_6__ {TYPE_2__* sighand; TYPE_1__* signal; } ;
struct TYPE_5__ {int /*<<< orphan*/  siglock; } ;
struct TYPE_4__ {int /*<<< orphan*/  audit_tty_log_passwd; int /*<<< orphan*/  audit_tty; } ;

/* Variables and functions */
 TYPE_3__* current ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void tty_audit_fork(struct signal_struct *sig)
{
	spin_lock_irq(&current->sighand->siglock);
	sig->audit_tty = current->signal->audit_tty;
	sig->audit_tty_log_passwd = current->signal->audit_tty_log_passwd;
	spin_unlock_irq(&current->sighand->siglock);
	sig->tty_audit_buf = NULL;
}