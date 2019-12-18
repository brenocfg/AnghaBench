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
struct TYPE_4__ {unsigned int eeprom_status; unsigned int eeprom_addr; unsigned int eeprom_cycle; unsigned int eeprom_slave; } ;
struct TYPE_6__ {TYPE_1__ m; } ;
struct TYPE_5__ {int eeprom_type; unsigned char* data; int changed; } ;

/* Variables and functions */
 int /*<<< orphan*/  EL_EEPROM ; 
 TYPE_3__ Pico ; 
 TYPE_2__ SRam ; 
 scalar_t__ SekCyclesDone () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ last_write ; 

__attribute__((used)) static void EEPROM_write_do(unsigned int d) // ???? ??la (l=SCL, a=SDA)
{
  unsigned int sreg = Pico.m.eeprom_status, saddr = Pico.m.eeprom_addr;
  unsigned int scyc = Pico.m.eeprom_cycle, ssa = Pico.m.eeprom_slave;

  elprintf(EL_EEPROM, "eeprom: scl/sda: %i/%i -> %i/%i, newtime=%i", (sreg&2)>>1, sreg&1,
    (d&2)>>1, d&1, SekCyclesDone() - last_write);
  saddr &= 0x1fff;

  if(sreg & d & 2) {
    // SCL was and is still high..
    if((sreg & 1) && !(d&1)) {
      // ..and SDA went low, means it's a start command, so clear internal addr reg and clock counter
      elprintf(EL_EEPROM, "eeprom: -start-");
      //saddr = 0;
      scyc = 0;
      sreg |= 8;
    } else if(!(sreg & 1) && (d&1)) {
      // SDA went high == stop command
      elprintf(EL_EEPROM, "eeprom: -stop-");
      sreg &= ~8;
    }
  }
  else if((sreg & 8) && !(sreg & 2) && (d&2))
  {
    // we are started and SCL went high - next cycle
    scyc++; // pre-increment
    if(SRam.eeprom_type) {
      // X24C02+
      if((ssa&1) && scyc == 18) {
        scyc = 9;
        saddr++; // next address in read mode
        /*if(SRam.eeprom_type==2) saddr&=0xff; else*/ saddr&=0x1fff; // mask
      }
      else if(SRam.eeprom_type == 2 && scyc == 27) scyc = 18;
      else if(scyc == 36) scyc = 27;
    } else {
      // X24C01
      if(scyc == 18) {
        scyc = 9;  // wrap
        if(saddr&1) { saddr+=2; saddr&=0xff; } // next addr in read mode
      }
    }
    elprintf(EL_EEPROM, "eeprom: scyc: %i", scyc);
  }
  else if((sreg & 8) && (sreg & 2) && !(d&2))
  {
    // we are started and SCL went low (falling edge)
    if(SRam.eeprom_type) {
      // X24C02+
      if(scyc == 9 || scyc == 18 || scyc == 27); // ACK cycles
      else if( (SRam.eeprom_type == 3 && scyc > 27) || (SRam.eeprom_type == 2 && scyc > 18) ) {
        if(!(ssa&1)) {
          // data write
          unsigned char *pm=SRam.data+saddr;
          *pm <<= 1; *pm |= d&1;
          if(scyc == 26 || scyc == 35) {
            saddr=(saddr&~0xf)|((saddr+1)&0xf); // only 4 (?) lowest bits are incremented
            elprintf(EL_EEPROM, "eeprom: write done, addr inc to: %x, last byte=%02x", saddr, *pm);
          }
          SRam.changed = 1;
        }
      } else if(scyc > 9) {
        if(!(ssa&1)) {
          // we latch another addr bit
          saddr<<=1;
          if(SRam.eeprom_type == 2) saddr&=0xff; else saddr&=0x1fff; // mask
          saddr|=d&1;
          if(scyc==17||scyc==26) {
            elprintf(EL_EEPROM, "eeprom: addr reg done: %x", saddr);
            if(scyc==17&&SRam.eeprom_type==2) { saddr&=0xff; saddr|=(ssa<<7)&0x700; } // add device bits too
          }
        }
      } else {
        // slave address
        ssa<<=1; ssa|=d&1;
        if(scyc==8) elprintf(EL_EEPROM, "eeprom: slave done: %x", ssa);
      }
    } else {
      // X24C01
      if(scyc == 9); // ACK cycle, do nothing
      else if(scyc > 9) {
        if(!(saddr&1)) {
          // data write
          unsigned char *pm=SRam.data+(saddr>>1);
          *pm <<= 1; *pm |= d&1;
          if(scyc == 17) {
            saddr=(saddr&0xf9)|((saddr+2)&6); // only 2 lowest bits are incremented
            elprintf(EL_EEPROM, "eeprom: write done, addr inc to: %x, last byte=%02x", saddr>>1, *pm);
          }
          SRam.changed = 1;
        }
      } else {
        // we latch another addr bit
        saddr<<=1; saddr|=d&1; saddr&=0xff;
        if(scyc==8) elprintf(EL_EEPROM, "eeprom: addr done: %x", saddr>>1);
      }
    }
  }

  sreg &= ~3; sreg |= d&3; // remember SCL and SDA
  Pico.m.eeprom_status  = (unsigned char) sreg;
  Pico.m.eeprom_cycle = (unsigned char) scyc;
  Pico.m.eeprom_slave = (unsigned char) ssa;
  Pico.m.eeprom_addr  = (unsigned short)saddr;
}