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
struct link_qual {void* false_cca; void* rx_failed; } ;

/* Variables and functions */
 int /*<<< orphan*/  STA_CSR0 ; 
 int /*<<< orphan*/  STA_CSR0_FCS_ERROR ; 
 int /*<<< orphan*/  STA_CSR1 ; 
 int /*<<< orphan*/  STA_CSR1_FALSE_CCA_ERROR ; 
 void* rt2x00_get_field32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00usb_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rt73usb_link_stats(struct rt2x00_dev *rt2x00dev,
			       struct link_qual *qual)
{
	u32 reg;

	/*
	 * Update FCS error count from register.
	 */
	rt2x00usb_register_read(rt2x00dev, STA_CSR0, &reg);
	qual->rx_failed = rt2x00_get_field32(reg, STA_CSR0_FCS_ERROR);

	/*
	 * Update False CCA count from register.
	 */
	rt2x00usb_register_read(rt2x00dev, STA_CSR1, &reg);
	qual->false_cca = rt2x00_get_field32(reg, STA_CSR1_FALSE_CCA_ERROR);
}