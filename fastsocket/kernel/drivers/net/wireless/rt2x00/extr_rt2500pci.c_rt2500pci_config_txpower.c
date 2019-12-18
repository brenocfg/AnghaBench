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

/* Variables and functions */
 int /*<<< orphan*/  RF3_TXPOWER ; 
 int /*<<< orphan*/  TXPOWER_TO_DEV (int const) ; 
 int /*<<< orphan*/  rt2500pci_rf_write (struct rt2x00_dev*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_rf_read (struct rt2x00_dev*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt2500pci_config_txpower(struct rt2x00_dev *rt2x00dev,
				     const int txpower)
{
	u32 rf3;

	rt2x00_rf_read(rt2x00dev, 3, &rf3);
	rt2x00_set_field32(&rf3, RF3_TXPOWER, TXPOWER_TO_DEV(txpower));
	rt2500pci_rf_write(rt2x00dev, 3, rf3);
}