#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int eeprom_status; int eeprom_addr; unsigned int eeprom_cycle; unsigned int eeprom_slave; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {unsigned int* data; unsigned int eeprom_bit_out; scalar_t__ eeprom_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EEPROM_write_do (int) ; 
 int /*<<< orphan*/  EL_EEPROM ; 
 TYPE_3__ Pico ; 
 TYPE_2__ SRam ; 
 unsigned int SekCyclesDone () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,...) ; 
 unsigned int last_write ; 

unsigned int EEPROM_read(void)
{
  unsigned int shift, d;
  unsigned int sreg, saddr, scyc, ssa, interval;

  // flush last pending write
  EEPROM_write_do(Pico.m.eeprom_status>>6);

  sreg = Pico.m.eeprom_status; saddr = Pico.m.eeprom_addr&0x1fff; scyc = Pico.m.eeprom_cycle; ssa = Pico.m.eeprom_slave;
  interval = SekCyclesDone() - last_write;
  d = (sreg>>6)&1; // use SDA as "open bus"

  // NBA Jam is nasty enough to read <before> raising the SCL and starting the new cycle.
  // this is probably valid because data changes occur while SCL is low and data can be read
  // before it's actual cycle begins.
  if (!(sreg&0x80) && interval >= 24) {
    elprintf(EL_EEPROM, "eeprom: early read, cycles=%i", interval);
    scyc++;
  }

  if (!(sreg & 8)); // not started, use open bus
  else if (scyc == 9 || scyc == 18 || scyc == 27) {
    elprintf(EL_EEPROM, "eeprom: r ack");
    d = 0;
  } else if (scyc > 9 && scyc < 18) {
    // started and first command word received
    shift = 17-scyc;
    if (SRam.eeprom_type) {
      // X24C02+
      if (ssa&1) {
        elprintf(EL_EEPROM, "eeprom: read: addr %02x, cycle %i, reg %02x", saddr, scyc, sreg);
	if (shift==0) elprintf(EL_EEPROM, "eeprom: read done, byte %02x", SRam.data[saddr]);
        d = (SRam.data[saddr]>>shift)&1;
      }
    } else {
      // X24C01
      if (saddr&1) {
        elprintf(EL_EEPROM, "eeprom: read: addr %02x, cycle %i, reg %02x", saddr>>1, scyc, sreg);
	if (shift==0) elprintf(EL_EEPROM, "eeprom: read done, byte %02x", SRam.data[saddr>>1]);
        d = (SRam.data[saddr>>1]>>shift)&1;
      }
    }
  }

  return (d << SRam.eeprom_bit_out);
}