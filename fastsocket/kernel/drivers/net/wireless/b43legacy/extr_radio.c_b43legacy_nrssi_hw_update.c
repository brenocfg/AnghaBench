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
struct b43legacy_wldev {int dummy; } ;
typedef  int /*<<< orphan*/  s16 ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_nrssi_hw_read (struct b43legacy_wldev*,int) ; 
 int /*<<< orphan*/  b43legacy_nrssi_hw_write (struct b43legacy_wldev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clamp_val (int /*<<< orphan*/ ,int,int) ; 

void b43legacy_nrssi_hw_update(struct b43legacy_wldev *dev, u16 val)
{
	u16 i;
	s16 tmp;

	for (i = 0; i < 64; i++) {
		tmp = b43legacy_nrssi_hw_read(dev, i);
		tmp -= val;
		tmp = clamp_val(tmp, -32, 31);
		b43legacy_nrssi_hw_write(dev, i, tmp);
	}
}