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
 int /*<<< orphan*/  DPORT_CLK_EN_RSA ; 
 int /*<<< orphan*/  DPORT_PERI_CLK_EN_REG ; 
 int /*<<< orphan*/  DPORT_PERI_RST_EN_REG ; 
 int /*<<< orphan*/  DPORT_REG_CLR_BIT (int /*<<< orphan*/ ,int) ; 
 int DPORT_REG_READ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPORT_REG_SET_BIT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int DPORT_RSA_MEM_PD ; 
 int /*<<< orphan*/  DPORT_RSA_PD_CTRL_REG ; 
 int DPORT_RST_EN_DIGITAL_SIGNATURE ; 
 int DPORT_RST_EN_RSA ; 
 int DPORT_RST_EN_SECURE_BOOT ; 
 int /*<<< orphan*/  RSA_QUERY_CLEAN_REG ; 
 int /*<<< orphan*/  _lock_acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mpi_lock ; 
 int /*<<< orphan*/  rsa_isr_initialise () ; 

void esp_mpi_acquire_hardware( void )
{
    /* newlib locks lazy initialize on ESP-IDF */
    _lock_acquire(&mpi_lock);

    DPORT_REG_SET_BIT(DPORT_PERI_CLK_EN_REG, DPORT_CLK_EN_RSA);
    /* also clear reset on digital signature & secure boot, otherwise RSA is held in reset */
    DPORT_REG_CLR_BIT(DPORT_PERI_RST_EN_REG, DPORT_RST_EN_RSA
                      | DPORT_RST_EN_DIGITAL_SIGNATURE
                      | DPORT_RST_EN_SECURE_BOOT);

    DPORT_REG_CLR_BIT(DPORT_RSA_PD_CTRL_REG, DPORT_RSA_MEM_PD);

    while(DPORT_REG_READ(RSA_QUERY_CLEAN_REG) != 1) {
    }
    // Note: from enabling RSA clock to here takes about 1.3us

#ifdef CONFIG_MBEDTLS_MPI_USE_INTERRUPT
    rsa_isr_initialise();
#endif
}