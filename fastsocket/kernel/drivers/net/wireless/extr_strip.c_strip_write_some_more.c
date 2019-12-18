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
struct tty_struct {int /*<<< orphan*/  flags; TYPE_1__* ops; struct strip* disc_data; } ;
struct strip {scalar_t__ magic; scalar_t__ tx_left; int tx_head; int tx_sbytes; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int (* write ) (struct tty_struct*,int,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ STRIP_MAGIC ; 
 int /*<<< orphan*/  TTY_DO_WRITE_WAKEUP ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netif_running (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strip_unlock (struct strip*) ; 
 int stub1 (struct tty_struct*,int,scalar_t__) ; 

__attribute__((used)) static void strip_write_some_more(struct tty_struct *tty)
{
	struct strip *strip_info = tty->disc_data;

	/* First make sure we're connected. */
	if (!strip_info || strip_info->magic != STRIP_MAGIC ||
	    !netif_running(strip_info->dev))
		return;

	if (strip_info->tx_left > 0) {
		int num_written =
		    tty->ops->write(tty, strip_info->tx_head,
				      strip_info->tx_left);
		strip_info->tx_left -= num_written;
		strip_info->tx_head += num_written;
#ifdef EXT_COUNTERS
		strip_info->tx_sbytes += num_written;
#endif
	} else {		/* Else start transmission of another packet */

		clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);
		strip_unlock(strip_info);
	}
}