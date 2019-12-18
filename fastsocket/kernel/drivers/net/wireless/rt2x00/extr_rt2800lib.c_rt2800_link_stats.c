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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int dummy; } ;
struct link_qual {int /*<<< orphan*/  rx_failed; } ;

/* Variables and functions */
 int /*<<< orphan*/  RX_STA_CNT0 ; 
 int /*<<< orphan*/  RX_STA_CNT0_CRC_ERR ; 
 int /*<<< orphan*/  rt2800_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void rt2800_link_stats(struct rt2x00_dev *rt2x00dev, struct link_qual *qual)
{
	u32 reg;

	/*
	 * Update FCS error count from register.
	 */
	rt2800_register_read(rt2x00dev, RX_STA_CNT0, &reg);
	qual->rx_failed = rt2x00_get_field32(reg, RX_STA_CNT0_CRC_ERR);
}