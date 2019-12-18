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
struct ps2dev {int /*<<< orphan*/  serio; int /*<<< orphan*/  cmd_mutex; } ;

/* Variables and functions */
 scalar_t__ i8042_check_port_owner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i8042_lock_chip () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 

void ps2_begin_command(struct ps2dev *ps2dev)
{
	mutex_lock(&ps2dev->cmd_mutex);

	if (i8042_check_port_owner(ps2dev->serio))
		i8042_lock_chip();
}