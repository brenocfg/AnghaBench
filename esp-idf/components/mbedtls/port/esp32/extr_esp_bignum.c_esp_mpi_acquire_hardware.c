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
 int /*<<< orphan*/  DPORT_REG_CLR_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DPORT_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPORT_RSA_PD ; 
 int /*<<< orphan*/  DPORT_RSA_PD_CTRL_REG ; 
 int /*<<< orphan*/  PERIPH_RSA_MODULE ; 
 int /*<<< orphan*/  RSA_CLEAN_REG ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpi_lock ; 
 int /*<<< orphan*/  periph_module_enable (int /*<<< orphan*/ ) ; 

void esp_mpi_acquire_hardware( void )
{
    /* newlib locks lazy initialize on ESP-IDF */
    _lock_acquire(&mpi_lock);

    /* Enable RSA hardware */
    periph_module_enable(PERIPH_RSA_MODULE);
    DPORT_REG_CLR_BIT(DPORT_RSA_PD_CTRL_REG, DPORT_RSA_PD);

    while(DPORT_REG_READ(RSA_CLEAN_REG) != 1);
    // Note: from enabling RSA clock to here takes about 1.3us
}