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
 int /*<<< orphan*/  DPORT_PERI_EN_AES ; 
 int /*<<< orphan*/  DPORT_PERI_RST_EN_REG ; 
 int /*<<< orphan*/  REG_CLR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_spinlock ; 
 int /*<<< orphan*/  portEXIT_CRITICAL (int /*<<< orphan*/ *) ; 

void esp_aes_release_hardware( void )
{
    /* Disable AES hardware */
    REG_SET_BIT(DPORT_PERI_RST_EN_REG, DPORT_PERI_EN_AES);
    /* Don't return other units to reset, as this pulls
       reset on RSA & SHA units, respectively. */
    REG_CLR_BIT(DPORT_PERI_CLK_EN_REG, DPORT_PERI_EN_AES);

    portEXIT_CRITICAL(&aes_spinlock);
}