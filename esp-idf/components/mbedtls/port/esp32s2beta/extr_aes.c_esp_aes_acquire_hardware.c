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

/* Variables and functions */
 int /*<<< orphan*/  DPORT_PERI_CLK_EN_REG ; 
 int DPORT_PERI_EN_AES ; 
 int DPORT_PERI_EN_DIGITAL_SIGNATURE ; 
 int /*<<< orphan*/  DPORT_PERI_RST_EN_REG ; 
 int /*<<< orphan*/  REG_CLR_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  aes_spinlock ; 
 int /*<<< orphan*/  portENTER_CRITICAL (int /*<<< orphan*/ *) ; 

void esp_aes_acquire_hardware( void )
{
    /* newlib locks lazy initialize on ESP-IDF */
    portENTER_CRITICAL(&aes_spinlock);

    /* Enable AES hardware */
    REG_SET_BIT(DPORT_PERI_CLK_EN_REG, DPORT_PERI_EN_AES);
    /* Clear reset on digital signature unit,
       otherwise AES unit is held in reset also. */
    REG_CLR_BIT(DPORT_PERI_RST_EN_REG,
                DPORT_PERI_EN_AES
                | DPORT_PERI_EN_DIGITAL_SIGNATURE);
}