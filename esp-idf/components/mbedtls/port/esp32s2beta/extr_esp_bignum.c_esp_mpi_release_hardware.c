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
 int /*<<< orphan*/  DPORT_PERI_EN_RSA ; 
 int /*<<< orphan*/  DPORT_PERI_RST_EN_REG ; 
 int /*<<< orphan*/  DPORT_REG_CLR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPORT_REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPORT_RSA_PD ; 
 int /*<<< orphan*/  DPORT_RSA_PD_CTRL_REG ; 
 int /*<<< orphan*/  _lock_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpi_lock ; 

void esp_mpi_release_hardware( void )
{
    DPORT_REG_SET_BIT(DPORT_RSA_PD_CTRL_REG, DPORT_RSA_PD);

    /* don't reset digital signature unit, as this resets AES also */
    DPORT_REG_SET_BIT(DPORT_PERI_RST_EN_REG, DPORT_PERI_EN_RSA);
    DPORT_REG_CLR_BIT(DPORT_PERI_CLK_EN_REG, DPORT_PERI_EN_RSA);

    _lock_release(&mpi_lock);
}