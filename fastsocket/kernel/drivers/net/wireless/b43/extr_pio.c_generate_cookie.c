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
typedef  int u16 ;
struct b43_pio_txqueue {scalar_t__ index; } ;
struct b43_pio_txpacket {int index; } ;

/* Variables and functions */

__attribute__((used)) static u16 generate_cookie(struct b43_pio_txqueue *q,
			   struct b43_pio_txpacket *pack)
{
	u16 cookie;

	/* Use the upper 4 bits of the cookie as
	 * PIO controller ID and store the packet index number
	 * in the lower 12 bits.
	 * Note that the cookie must never be 0, as this
	 * is a special value used in RX path.
	 * It can also not be 0xFFFF because that is special
	 * for multicast frames.
	 */
	cookie = (((u16)q->index + 1) << 12);
	cookie |= pack->index;

	return cookie;
}