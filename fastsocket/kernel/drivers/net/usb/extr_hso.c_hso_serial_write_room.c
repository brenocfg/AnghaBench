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
struct hso_serial {int tx_data_length; int tx_buffer_count; int /*<<< orphan*/  serial_lock; } ;

/* Variables and functions */
 struct hso_serial* get_serial_by_tty (struct tty_struct*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int hso_serial_write_room(struct tty_struct *tty)
{
	struct hso_serial *serial = get_serial_by_tty(tty);
	int room;
	unsigned long flags;

	spin_lock_irqsave(&serial->serial_lock, flags);
	room = serial->tx_data_length - serial->tx_buffer_count;
	spin_unlock_irqrestore(&serial->serial_lock, flags);

	/* return free room */
	return room;
}