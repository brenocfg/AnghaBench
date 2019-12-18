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
struct urb {int actual_length; int transfer_buffer; } ;
struct tty_struct {int /*<<< orphan*/  flags; } ;
struct hso_serial {int curr_rx_urb_offset; scalar_t__* rx_urb_filled; int /*<<< orphan*/  tty; } ;

/* Variables and functions */
 int /*<<< orphan*/  D1 (char*) ; 
 int /*<<< orphan*/  TTY_THROTTLED ; 
 size_t hso_urb_to_index (struct hso_serial*,struct urb*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int tty_insert_flip_string (struct tty_struct*,int,int) ; 
 struct tty_struct* tty_kref_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_kref_put (struct tty_struct*) ; 

__attribute__((used)) static int put_rxbuf_data(struct urb *urb, struct hso_serial *serial)
{
	struct tty_struct *tty;
	int write_length_remaining = 0;
	int curr_write_len;

	/* Sanity check */
	if (urb == NULL || serial == NULL) {
		D1("serial = NULL");
		return -2;
	}

	/* All callers to put_rxbuf_data hold serial_lock */
	tty = tty_kref_get(serial->tty);

	/* Push data to tty */
	if (tty) {
		write_length_remaining = urb->actual_length -
			serial->curr_rx_urb_offset;
		D1("data to push to tty");
		while (write_length_remaining) {
			if (test_bit(TTY_THROTTLED, &tty->flags)) {
				tty_kref_put(tty);
				return -1;
			}
			curr_write_len =  tty_insert_flip_string
				(tty, urb->transfer_buffer +
				 serial->curr_rx_urb_offset,
				 write_length_remaining);
			serial->curr_rx_urb_offset += curr_write_len;
			write_length_remaining -= curr_write_len;
			tty_flip_buffer_push(tty);
		}
	}
	if (write_length_remaining == 0) {
		serial->curr_rx_urb_offset = 0;
		serial->rx_urb_filled[hso_urb_to_index(serial, urb)] = 0;
	}
	tty_kref_put(tty);
	return write_length_remaining;
}