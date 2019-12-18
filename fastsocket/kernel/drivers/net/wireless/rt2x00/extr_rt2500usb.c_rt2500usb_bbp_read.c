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
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u16 ;
struct rt2x00_dev {int /*<<< orphan*/  csr_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  PHY_CSR7 ; 
 int /*<<< orphan*/  PHY_CSR7_DATA ; 
 int /*<<< orphan*/  PHY_CSR7_READ_CONTROL ; 
 int /*<<< orphan*/  PHY_CSR7_REG_ID ; 
 scalar_t__ WAIT_FOR_BBP (struct rt2x00_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2500usb_register_read_lock (struct rt2x00_dev*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rt2500usb_register_write_lock (struct rt2x00_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rt2x00_get_field16 (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2x00_set_field16 (scalar_t__*,int /*<<< orphan*/ ,unsigned int const) ; 

__attribute__((used)) static void rt2500usb_bbp_read(struct rt2x00_dev *rt2x00dev,
			       const unsigned int word, u8 *value)
{
	u16 reg;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the BBP becomes available, afterwards we
	 * can safely write the read request into the register.
	 * After the data has been written, we wait until hardware
	 * returns the correct value, if at any time the register
	 * doesn't become available in time, reg will be 0xffffffff
	 * which means we return 0xff to the caller.
	 */
	if (WAIT_FOR_BBP(rt2x00dev, &reg)) {
		reg = 0;
		rt2x00_set_field16(&reg, PHY_CSR7_REG_ID, word);
		rt2x00_set_field16(&reg, PHY_CSR7_READ_CONTROL, 1);

		rt2500usb_register_write_lock(rt2x00dev, PHY_CSR7, reg);

		if (WAIT_FOR_BBP(rt2x00dev, &reg))
			rt2500usb_register_read_lock(rt2x00dev, PHY_CSR7, &reg);
	}

	*value = rt2x00_get_field16(reg, PHY_CSR7_DATA);

	mutex_unlock(&rt2x00dev->csr_mutex);
}