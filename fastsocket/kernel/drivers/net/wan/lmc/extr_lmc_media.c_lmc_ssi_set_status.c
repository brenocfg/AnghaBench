#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ clock_source; scalar_t__ clock_rate; } ;
struct TYPE_16__ {TYPE_1__* lmc_media; TYPE_3__ ictl; scalar_t__ lmc_timing; } ;
typedef  TYPE_2__ lmc_softc_t ;
typedef  TYPE_3__ lmc_ctl_t ;
struct TYPE_15__ {int /*<<< orphan*/  (* set_speed ) (TYPE_2__* const,TYPE_3__*) ;int /*<<< orphan*/  (* set_clock_source ) (TYPE_2__* const,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ LMC_CTL_CLOCK_SOURCE_EXT ; 
 scalar_t__ LMC_CTL_CLOCK_SOURCE_INT ; 
 int /*<<< orphan*/  lmc_set_protocol (TYPE_2__* const,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__* const,scalar_t__) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__* const,TYPE_3__*) ; 
 int /*<<< orphan*/  stub3 (TYPE_2__* const,scalar_t__) ; 
 int /*<<< orphan*/  stub4 (TYPE_2__* const,scalar_t__) ; 
 int /*<<< orphan*/  stub5 (TYPE_2__* const,TYPE_3__*) ; 

__attribute__((used)) static void
lmc_ssi_set_status (lmc_softc_t * const sc, lmc_ctl_t * ctl)
{
  if (ctl == NULL)
    {
      sc->lmc_media->set_clock_source (sc, sc->ictl.clock_source);
      sc->lmc_media->set_speed (sc, &sc->ictl);
      lmc_set_protocol (sc, NULL);

      return;
    }

  /*
   * check for change in clock source
   */
  if (ctl->clock_source == LMC_CTL_CLOCK_SOURCE_INT
      && sc->ictl.clock_source == LMC_CTL_CLOCK_SOURCE_EXT)
    {
      sc->lmc_media->set_clock_source (sc, LMC_CTL_CLOCK_SOURCE_INT);
      sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_INT;
    }
  else if (ctl->clock_source == LMC_CTL_CLOCK_SOURCE_EXT
	   && sc->ictl.clock_source == LMC_CTL_CLOCK_SOURCE_INT)
    {
      sc->lmc_media->set_clock_source (sc, LMC_CTL_CLOCK_SOURCE_EXT);
      sc->lmc_timing = LMC_CTL_CLOCK_SOURCE_EXT;
    }

  if (ctl->clock_rate != sc->ictl.clock_rate)
    sc->lmc_media->set_speed (sc, ctl);

  lmc_set_protocol (sc, ctl);
}