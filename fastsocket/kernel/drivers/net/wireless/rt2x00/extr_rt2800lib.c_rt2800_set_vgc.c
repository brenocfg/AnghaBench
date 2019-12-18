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
typedef  int u8 ;
struct rt2x00_dev {int dummy; } ;
struct link_qual {int vgc_level; int rssi; int vgc_level_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  RT5592 ; 
 int /*<<< orphan*/  rt2800_bbp_write (struct rt2x00_dev*,int,int) ; 
 int /*<<< orphan*/  rt2800_bbp_write_with_rx_chain (struct rt2x00_dev*,int,int) ; 
 scalar_t__ rt2x00_rt (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void rt2800_set_vgc(struct rt2x00_dev *rt2x00dev,
				  struct link_qual *qual, u8 vgc_level)
{
	if (qual->vgc_level != vgc_level) {
		if (rt2x00_rt(rt2x00dev, RT5592)) {
			rt2800_bbp_write(rt2x00dev, 83, qual->rssi > -65 ? 0x4a : 0x7a);
			rt2800_bbp_write_with_rx_chain(rt2x00dev, 66, vgc_level);
		} else
			rt2800_bbp_write(rt2x00dev, 66, vgc_level);
		qual->vgc_level = vgc_level;
		qual->vgc_level_reg = vgc_level;
	}
}