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
typedef  int /*<<< orphan*/  tmp ;
struct serial_struct {int port; int /*<<< orphan*/  custom_divisor; int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  baud_base; int /*<<< orphan*/  flags; int /*<<< orphan*/  irq; int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;
struct e100_serial {int /*<<< orphan*/  custom_divisor; int /*<<< orphan*/  closing_wait; int /*<<< orphan*/  close_delay; int /*<<< orphan*/  baud_base; int /*<<< orphan*/  flags; int /*<<< orphan*/  irq; scalar_t__ ioport; int /*<<< orphan*/  line; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_to_user (struct serial_struct*,struct serial_struct*,int) ; 
 int /*<<< orphan*/  memset (struct serial_struct*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
get_serial_info(struct e100_serial * info,
		struct serial_struct * retinfo)
{
	struct serial_struct tmp;

	/* this is all probably wrong, there are a lot of fields
	 * here that we don't have in e100_serial and maybe we
	 * should set them to something else than 0.
	 */

	if (!retinfo)
		return -EFAULT;
	memset(&tmp, 0, sizeof(tmp));
	tmp.type = info->type;
	tmp.line = info->line;
	tmp.port = (int)info->ioport;
	tmp.irq = info->irq;
	tmp.flags = info->flags;
	tmp.baud_base = info->baud_base;
	tmp.close_delay = info->close_delay;
	tmp.closing_wait = info->closing_wait;
	tmp.custom_divisor = info->custom_divisor;
	if (copy_to_user(retinfo, &tmp, sizeof(*retinfo)))
		return -EFAULT;
	return 0;
}