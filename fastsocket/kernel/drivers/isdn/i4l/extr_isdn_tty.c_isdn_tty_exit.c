#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ xmit_buf; scalar_t__ fax; } ;
typedef  TYPE_2__ modem_info ;
struct TYPE_5__ {int /*<<< orphan*/ * tty_modem; TYPE_2__* info; } ;
struct TYPE_7__ {TYPE_1__ mdm; } ;

/* Variables and functions */
 int ISDN_MAX_CHANNELS ; 
 TYPE_4__* dev ; 
 int /*<<< orphan*/  isdn_tty_cleanup_xmit (TYPE_2__*) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  put_tty_driver (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_unregister_driver (int /*<<< orphan*/ *) ; 

void
isdn_tty_exit(void)
{
	modem_info *info;
	int i;

	for (i = 0; i < ISDN_MAX_CHANNELS; i++) {
		info = &dev->mdm.info[i];
		isdn_tty_cleanup_xmit(info);
#ifdef CONFIG_ISDN_TTY_FAX
		kfree(info->fax);
#endif
		kfree(info->xmit_buf - 4);
	}
	tty_unregister_driver(dev->mdm.tty_modem);
	put_tty_driver(dev->mdm.tty_modem);
	dev->mdm.tty_modem = NULL;
}