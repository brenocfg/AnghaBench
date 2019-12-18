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
struct rt2x00_dev {int dummy; } ;
struct rf_channel {int rf1; int rf3; int rf2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CNT0 ; 
 int /*<<< orphan*/  RF1_TUNER ; 
 int /*<<< orphan*/  RF2420 ; 
 int /*<<< orphan*/  RF3_TUNER ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt2400pci_rf_write (struct rt2x00_dev*,int,int) ; 
 scalar_t__ rt2x00_rf (struct rt2x00_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void rt2400pci_config_channel(struct rt2x00_dev *rt2x00dev,
				     struct rf_channel *rf)
{
	/*
	 * Switch on tuning bits.
	 */
	rt2x00_set_field32(&rf->rf1, RF1_TUNER, 1);
	rt2x00_set_field32(&rf->rf3, RF3_TUNER, 1);

	rt2400pci_rf_write(rt2x00dev, 1, rf->rf1);
	rt2400pci_rf_write(rt2x00dev, 2, rf->rf2);
	rt2400pci_rf_write(rt2x00dev, 3, rf->rf3);

	/*
	 * RF2420 chipset don't need any additional actions.
	 */
	if (rt2x00_rf(rt2x00dev, RF2420))
		return;

	/*
	 * For the RT2421 chipsets we need to write an invalid
	 * reference clock rate to activate auto_tune.
	 * After that we set the value back to the correct channel.
	 */
	rt2400pci_rf_write(rt2x00dev, 1, rf->rf1);
	rt2400pci_rf_write(rt2x00dev, 2, 0x000c2a32);
	rt2400pci_rf_write(rt2x00dev, 3, rf->rf3);

	msleep(1);

	rt2400pci_rf_write(rt2x00dev, 1, rf->rf1);
	rt2400pci_rf_write(rt2x00dev, 2, rf->rf2);
	rt2400pci_rf_write(rt2x00dev, 3, rf->rf3);

	msleep(1);

	/*
	 * Switch off tuning bits.
	 */
	rt2x00_set_field32(&rf->rf1, RF1_TUNER, 0);
	rt2x00_set_field32(&rf->rf3, RF3_TUNER, 0);

	rt2400pci_rf_write(rt2x00dev, 1, rf->rf1);
	rt2400pci_rf_write(rt2x00dev, 3, rf->rf3);

	/*
	 * Clear false CRC during channel switch.
	 */
	rt2x00mmio_register_read(rt2x00dev, CNT0, &rf->rf1);
}