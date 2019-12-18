#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tty_struct {int /*<<< orphan*/  name; struct async_struct* driver_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
struct async_struct {TYPE_1__ xmit; } ;

/* Variables and functions */
 int CIRC_SPACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SERIAL_XMIT_SIZE ; 
 scalar_t__ serial_paranoia_check (struct async_struct*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int rs_write_room(struct tty_struct *tty)
{
	struct async_struct *info = tty->driver_data;

	if (serial_paranoia_check(info, tty->name, "rs_write_room"))
		return 0;
	return CIRC_SPACE(info->xmit.head, info->xmit.tail, SERIAL_XMIT_SIZE);
}