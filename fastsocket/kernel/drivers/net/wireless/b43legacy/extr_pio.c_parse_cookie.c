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
struct b43legacy_pio {struct b43legacy_pioqueue* queue3; struct b43legacy_pioqueue* queue2; struct b43legacy_pioqueue* queue1; struct b43legacy_pioqueue* queue0; } ;
struct b43legacy_wldev {struct b43legacy_pio pio; } ;
struct b43legacy_pioqueue {struct b43legacy_pio_txpacket* tx_packets_cache; } ;
struct b43legacy_pio_txpacket {int dummy; } ;

/* Variables and functions */
 int B43legacy_PIO_MAXTXPACKETS ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 

__attribute__((used)) static
struct b43legacy_pioqueue *parse_cookie(struct b43legacy_wldev *dev,
					u16 cookie,
					struct b43legacy_pio_txpacket **packet)
{
	struct b43legacy_pio *pio = &dev->pio;
	struct b43legacy_pioqueue *queue = NULL;
	int packetindex;

	switch (cookie & 0xF000) {
	case 0x0000:
		queue = pio->queue0;
		break;
	case 0x1000:
		queue = pio->queue1;
		break;
	case 0x2000:
		queue = pio->queue2;
		break;
	case 0x3000:
		queue = pio->queue3;
		break;
	default:
		B43legacy_WARN_ON(1);
	}
	packetindex = (cookie & 0x0FFF);
	B43legacy_WARN_ON(!(packetindex >= 0 && packetindex
			  < B43legacy_PIO_MAXTXPACKETS));
	*packet = &(queue->tx_packets_cache[packetindex]);

	return queue;
}