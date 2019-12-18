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
struct tty_struct {struct channel* driver_data; } ;
struct channel {scalar_t__ magic; } ;

/* Variables and functions */
 scalar_t__ EPCA_MAGIC ; 
 struct channel* digi_channels ; 
 size_t nbdevs ; 

__attribute__((used)) static struct channel *verifyChannel(struct tty_struct *tty)
{
	/*
	 * This routine basically provides a sanity check. It insures that the
	 * channel returned is within the proper range of addresses as well as
	 * properly initialized. If some bogus info gets passed in
	 * through tty->driver_data this should catch it.
	 */
	if (tty) {
		struct channel *ch = tty->driver_data;
		if (ch >= &digi_channels[0] && ch < &digi_channels[nbdevs]) {
			if (ch->magic == EPCA_MAGIC)
				return ch;
		}
	}
	return NULL;
}