#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cardtype; } ;
struct TYPE_6__ {TYPE_1__ ictl; } ;
typedef  TYPE_2__ lmc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  LMC_CTL_CARDTYPE_LMC5200 ; 
 int /*<<< orphan*/  LMC_GEP_HSSI_CLOCK ; 
 int /*<<< orphan*/  lmc_gpio_mkoutput (TYPE_2__* const,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lmc_hssi_init (lmc_softc_t * const sc)
{
  sc->ictl.cardtype = LMC_CTL_CARDTYPE_LMC5200;

  lmc_gpio_mkoutput (sc, LMC_GEP_HSSI_CLOCK);
}