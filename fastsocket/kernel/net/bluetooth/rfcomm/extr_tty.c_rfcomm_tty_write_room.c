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
struct tty_struct {scalar_t__ driver_data; } ;
struct rfcomm_dev {int /*<<< orphan*/  wmem_alloc; int /*<<< orphan*/  dlc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BT_DBG (char*,struct tty_struct*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int rfcomm_room (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rfcomm_tty_write_room(struct tty_struct *tty)
{
	struct rfcomm_dev *dev = (struct rfcomm_dev *) tty->driver_data;
	int room;

	BT_DBG("tty %p", tty);

	if (!dev || !dev->dlc)
		return 0;

	room = rfcomm_room(dev->dlc) - atomic_read(&dev->wmem_alloc);
	if (room < 0)
		room = 0;

	return room;
}