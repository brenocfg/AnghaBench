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
struct TYPE_4__ {int /*<<< orphan*/  lmc_miireg16; } ;
typedef  TYPE_1__ lmc_softc_t ;

/* Variables and functions */
 int LMC_LINK_UP ; 
 int /*<<< orphan*/  LMC_MII16_HSSI_TA ; 
 int /*<<< orphan*/  lmc_mii_writereg (TYPE_1__* const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lmc_hssi_set_link_status (lmc_softc_t * const sc, int state)
{
  if (state == LMC_LINK_UP)
    sc->lmc_miireg16 |= LMC_MII16_HSSI_TA;
  else
    sc->lmc_miireg16 &= ~LMC_MII16_HSSI_TA;

  lmc_mii_writereg (sc, 0, 16, sc->lmc_miireg16);
}