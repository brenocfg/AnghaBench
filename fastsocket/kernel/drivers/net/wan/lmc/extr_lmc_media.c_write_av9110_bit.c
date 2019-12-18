#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lmc_gpio; } ;
typedef  TYPE_1__ lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CSR_WRITE (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LMC_GEP_CLK ; 
 int /*<<< orphan*/  LMC_GEP_DATA ; 
 int /*<<< orphan*/  csr_gp ; 

__attribute__((used)) static inline void
write_av9110_bit (lmc_softc_t * sc, int c)
{
  /*
   * set the data bit as we need it.
   */
  sc->lmc_gpio &= ~(LMC_GEP_CLK);
  if (c & 0x01)
    sc->lmc_gpio |= LMC_GEP_DATA;
  else
    sc->lmc_gpio &= ~(LMC_GEP_DATA);
  LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);

  /*
   * set the clock to high
   */
  sc->lmc_gpio |= LMC_GEP_CLK;
  LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);

  /*
   * set the clock to low again.
   */
  sc->lmc_gpio &= ~(LMC_GEP_CLK);
  LMC_CSR_WRITE (sc, csr_gp, sc->lmc_gpio);
}