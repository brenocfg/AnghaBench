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
typedef  size_t u16 ;
struct b43_wldev {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (size_t const*) ; 
 int R2059_ALL ; 
 size_t const R2059_C1 ; 
 size_t const R2059_C2 ; 
 size_t const R2059_C3 ; 
 int /*<<< orphan*/  b43_radio_mask (struct b43_wldev*,size_t const,int) ; 
 int /*<<< orphan*/  b43_radio_maskset (struct b43_wldev*,size_t const,int,int) ; 
 int b43_radio_read (struct b43_wldev*,size_t const) ; 
 int /*<<< orphan*/  b43_radio_set (struct b43_wldev*,size_t const,int) ; 
 int /*<<< orphan*/  b43_radio_write (struct b43_wldev*,int,size_t const) ; 
 int /*<<< orphan*/  b43err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void b43_radio_2059_init(struct b43_wldev *dev)
{
	const u16 routing[] = { R2059_C1, R2059_C2, R2059_C3 };
	const u16 radio_values[3][2] = {
		{ 0x61, 0xE9 }, { 0x69, 0xD5 }, { 0x73, 0x99 },
	};
	u16 i, j;

	b43_radio_write(dev, R2059_ALL | 0x51, 0x0070);
	b43_radio_write(dev, R2059_ALL | 0x5a, 0x0003);

	for (i = 0; i < ARRAY_SIZE(routing); i++)
		b43_radio_set(dev, routing[i] | 0x146, 0x3);

	b43_radio_set(dev, 0x2e, 0x0078);
	b43_radio_set(dev, 0xc0, 0x0080);
	msleep(2);
	b43_radio_mask(dev, 0x2e, ~0x0078);
	b43_radio_mask(dev, 0xc0, ~0x0080);

	if (1) { /* FIXME */
		b43_radio_set(dev, R2059_C3 | 0x4, 0x1);
		udelay(10);
		b43_radio_set(dev, R2059_C3 | 0x0BF, 0x1);
		b43_radio_maskset(dev, R2059_C3 | 0x19B, 0x3, 0x2);

		b43_radio_set(dev, R2059_C3 | 0x4, 0x2);
		udelay(100);
		b43_radio_mask(dev, R2059_C3 | 0x4, ~0x2);

		for (i = 0; i < 10000; i++) {
			if (b43_radio_read(dev, R2059_C3 | 0x145) & 1) {
				i = 0;
				break;
			}
			udelay(100);
		}
		if (i)
			b43err(dev->wl, "radio 0x945 timeout\n");

		b43_radio_mask(dev, R2059_C3 | 0x4, ~0x1);
		b43_radio_set(dev, 0xa, 0x60);

		for (i = 0; i < 3; i++) {
			b43_radio_write(dev, 0x17F, radio_values[i][0]);
			b43_radio_write(dev, 0x13D, 0x6E);
			b43_radio_write(dev, 0x13E, radio_values[i][1]);
			b43_radio_write(dev, 0x13C, 0x55);

			for (j = 0; j < 10000; j++) {
				if (b43_radio_read(dev, 0x140) & 2) {
					j = 0;
					break;
				}
				udelay(500);
			}
			if (j)
				b43err(dev->wl, "radio 0x140 timeout\n");

			b43_radio_write(dev, 0x13C, 0x15);
		}

		b43_radio_mask(dev, 0x17F, ~0x1);
	}

	b43_radio_mask(dev, 0x11, ~0x0008);
}