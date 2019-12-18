#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int* s68k_regs; } ;

/* Variables and functions */
 int EL_CD ; 
 int EL_INTS ; 
 int PCDS_IEN4 ; 
 int /*<<< orphan*/  PCD_EVENT_CDC ; 
 TYPE_1__* Pico_mcd ; 
 int /*<<< orphan*/  SekInterruptS68k (int) ; 
 int /*<<< orphan*/  cdd_update () ; 
 int /*<<< orphan*/  elprintf (int,char*) ; 
 int /*<<< orphan*/  pcd_event_schedule (unsigned int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void pcd_cdc_event(unsigned int now)
{
  // 75Hz CDC update
  cdd_update();

  /* check if a new CDD command has been processed */
  if (!(Pico_mcd->s68k_regs[0x4b] & 0xf0))
  {
    /* reset CDD command wait flag */
    Pico_mcd->s68k_regs[0x4b] = 0xf0;

    if (Pico_mcd->s68k_regs[0x33] & PCDS_IEN4) {
      elprintf(EL_INTS|EL_CD, "s68k: cdd irq 4");
      SekInterruptS68k(4);
    }
  }

  pcd_event_schedule(now, PCD_EVENT_CDC, 12500000/75);
}