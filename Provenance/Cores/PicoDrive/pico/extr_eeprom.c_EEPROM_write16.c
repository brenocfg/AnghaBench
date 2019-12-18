#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int eeprom_status; } ;
struct TYPE_4__ {TYPE_1__ m; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_upd_pending (unsigned int) ; 
 int /*<<< orphan*/  EEPROM_write_do (int) ; 
 int /*<<< orphan*/  EL_EEPROM ; 
 TYPE_2__ Pico ; 
 int SekCyclesDone () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,int) ; 
 int last_write ; 

void EEPROM_write16(unsigned int d)
{
  // this diff must be at most 16 for NBA Jam to work
  if (SekCyclesDone() - last_write < 16) {
    // just update pending state
    elprintf(EL_EEPROM, "eeprom: skip because cycles=%i",
        SekCyclesDone() - last_write);
    EEPROM_upd_pending(d);
  } else {
    int srs = Pico.m.eeprom_status;
    EEPROM_write_do(srs >> 6); // execute pending
    EEPROM_upd_pending(d);
    if ((srs ^ Pico.m.eeprom_status) & 0xc0) // update time only if SDA/SCL changed
      last_write = SekCyclesDone();
  }
}