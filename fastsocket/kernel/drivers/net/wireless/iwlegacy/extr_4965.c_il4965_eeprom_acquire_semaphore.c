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
typedef  scalar_t__ u16 ;
struct il_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG ; 
 int /*<<< orphan*/  CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM ; 
 scalar_t__ EEPROM_SEM_RETRY_LIMIT ; 
 int /*<<< orphan*/  EEPROM_SEM_TIMEOUT ; 
 int _il_poll_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il_set_bit (struct il_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
il4965_eeprom_acquire_semaphore(struct il_priv *il)
{
	u16 count;
	int ret;

	for (count = 0; count < EEPROM_SEM_RETRY_LIMIT; count++) {
		/* Request semaphore */
		il_set_bit(il, CSR_HW_IF_CONFIG_REG,
			   CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM);

		/* See if we got it */
		ret =
		    _il_poll_bit(il, CSR_HW_IF_CONFIG_REG,
				 CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM,
				 CSR_HW_IF_CONFIG_REG_BIT_EEPROM_OWN_SEM,
				 EEPROM_SEM_TIMEOUT);
		if (ret >= 0)
			return ret;
	}

	return ret;
}