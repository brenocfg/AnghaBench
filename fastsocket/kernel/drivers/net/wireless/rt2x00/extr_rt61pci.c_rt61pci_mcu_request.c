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
typedef  int /*<<< orphan*/  u32 ;
struct rt2x00_dev {int /*<<< orphan*/  csr_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2M_MAILBOX_CSR ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR_ARG0 ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR_ARG1 ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR_CMD_TOKEN ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR_OWNER ; 
 int /*<<< orphan*/  HOST_CMD_CSR ; 
 int /*<<< orphan*/  HOST_CMD_CSR_HOST_COMMAND ; 
 int /*<<< orphan*/  HOST_CMD_CSR_INTERRUPT_MCU ; 
 scalar_t__ WAIT_FOR_MCU (struct rt2x00_dev*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  rt2x00mmio_register_read (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2x00mmio_register_write (struct rt2x00_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rt61pci_mcu_request(struct rt2x00_dev *rt2x00dev,
				const u8 command, const u8 token,
				const u8 arg0, const u8 arg1)
{
	u32 reg;

	mutex_lock(&rt2x00dev->csr_mutex);

	/*
	 * Wait until the MCU becomes available, afterwards we
	 * can safely write the new data into the register.
	 */
	if (WAIT_FOR_MCU(rt2x00dev, &reg)) {
		rt2x00_set_field32(&reg, H2M_MAILBOX_CSR_OWNER, 1);
		rt2x00_set_field32(&reg, H2M_MAILBOX_CSR_CMD_TOKEN, token);
		rt2x00_set_field32(&reg, H2M_MAILBOX_CSR_ARG0, arg0);
		rt2x00_set_field32(&reg, H2M_MAILBOX_CSR_ARG1, arg1);
		rt2x00mmio_register_write(rt2x00dev, H2M_MAILBOX_CSR, reg);

		rt2x00mmio_register_read(rt2x00dev, HOST_CMD_CSR, &reg);
		rt2x00_set_field32(&reg, HOST_CMD_CSR_HOST_COMMAND, command);
		rt2x00_set_field32(&reg, HOST_CMD_CSR_INTERRUPT_MCU, 1);
		rt2x00mmio_register_write(rt2x00dev, HOST_CMD_CSR, reg);
	}

	mutex_unlock(&rt2x00dev->csr_mutex);

}