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
struct notifier_block {int dummy; } ;
struct fc_lport {int dummy; } ;

/* Variables and functions */
#define  FC_LPORT_EV_ADD 129 
#define  FC_LPORT_EV_DEL 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  ft_lport_add (struct fc_lport*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ft_lport_del (struct fc_lport*,int /*<<< orphan*/ *) ; 

int ft_lport_notify(struct notifier_block *nb, unsigned long event, void *arg)
{
	struct fc_lport *lport = arg;

	switch (event) {
	case FC_LPORT_EV_ADD:
		ft_lport_add(lport, NULL);
		break;
	case FC_LPORT_EV_DEL:
		ft_lport_del(lport, NULL);
		break;
	}
	return NOTIFY_DONE;
}