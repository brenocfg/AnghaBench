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
typedef  scalar_t__ u32 ;
struct rt2x00_dev {int /*<<< orphan*/  csr_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  H2M_MAILBOX_CSR ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR_ARG0 ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR_ARG1 ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR_CMD_TOKEN ; 
 int /*<<< orphan*/  H2M_MAILBOX_CSR_OWNER ; 
 int /*<<< orphan*/  HOST_CMD_CSR ; 
 int /*<<< orphan*/  HOST_CMD_CSR_HOST_COMMAND ; 
 scalar_t__ WAIT_FOR_MCU (struct rt2x00_dev*,scalar_t__*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2800_register_write_lock (struct rt2x00_dev*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ rt2x00_is_soc (struct rt2x00_dev*) ; 
 int /*<<< orphan*/  rt2x00_set_field32 (scalar_t__*,int /*<<< orphan*/ ,int const) ; 

void rt2800_mcu_request(struct rt2x00_dev *rt2x00dev,
			const u8 command, const u8 token,
			const u8 arg0, const u8 arg1)
{
	u32 reg;

	/*
	 * SOC devices don't support MCU requests.
	 */
	if (rt2x00_is_soc(rt2x00dev))
		return;

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
		rt2800_register_write_lock(rt2x00dev, H2M_MAILBOX_CSR, reg);

		reg = 0;
		rt2x00_set_field32(&reg, HOST_CMD_CSR_HOST_COMMAND, command);
		rt2800_register_write_lock(rt2x00dev, HOST_CMD_CSR, reg);
	}

	mutex_unlock(&rt2x00dev->csr_mutex);
}