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
typedef  unsigned char uint8 ;
struct TYPE_4__ {int* s68k_regs; } ;
struct TYPE_3__ {unsigned char ifstat; int dbc; unsigned char** head; size_t* ctrl; int pt; int wa; unsigned char* stat; int ifctrl; } ;

/* Variables and functions */
 unsigned char BIT_DECI ; 
 int BIT_DTEI ; 
 int BIT_DTEIEN ; 
 size_t BIT_SHDREN ; 
 unsigned char BIT_VALST ; 
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  SekInterruptClearS68k (int) ; 
 TYPE_1__ cdc ; 

unsigned char cdc_reg_r(void)
{
  switch (Pico_mcd->s68k_regs[0x04+1] & 0x0F)
  {
    case 0x01:  /* IFSTAT */
      Pico_mcd->s68k_regs[0x04+1] = 0x02;
      return cdc.ifstat;

    case 0x02:  /* DBCL */
      Pico_mcd->s68k_regs[0x04+1] = 0x03;
      return cdc.dbc & 0xff;

    case 0x03:  /* DBCH */
      Pico_mcd->s68k_regs[0x04+1] = 0x04;
      return (cdc.dbc >> 8) & 0xff;

    case 0x04:  /* HEAD0 */
      Pico_mcd->s68k_regs[0x04+1] = 0x05;
      return cdc.head[cdc.ctrl[1] & BIT_SHDREN][0];

    case 0x05:  /* HEAD1 */
      Pico_mcd->s68k_regs[0x04+1] = 0x06;
      return cdc.head[cdc.ctrl[1] & BIT_SHDREN][1];

    case 0x06:  /* HEAD2 */
      Pico_mcd->s68k_regs[0x04+1] = 0x07;
      return cdc.head[cdc.ctrl[1] & BIT_SHDREN][2];

    case 0x07:  /* HEAD3 */
      Pico_mcd->s68k_regs[0x04+1] = 0x08;
      return cdc.head[cdc.ctrl[1] & BIT_SHDREN][3];

    case 0x08:  /* PTL */
      Pico_mcd->s68k_regs[0x04+1] = 0x09;
      return cdc.pt & 0xff;

    case 0x09:  /* PTH */
      Pico_mcd->s68k_regs[0x04+1] = 0x0a;
      return (cdc.pt >> 8) & 0xff;

    case 0x0a:  /* WAL */
      Pico_mcd->s68k_regs[0x04+1] = 0x0b;
      return cdc.wa & 0xff;

    case 0x0b:  /* WAH */
      Pico_mcd->s68k_regs[0x04+1] = 0x0c;
      return (cdc.wa >> 8) & 0xff;

    case 0x0c: /* STAT0 */
      Pico_mcd->s68k_regs[0x04+1] = 0x0d;
      return cdc.stat[0];

    case 0x0d: /* STAT1 (always return 0) */
      Pico_mcd->s68k_regs[0x04+1] = 0x0e;
      return 0x00;

    case 0x0e:  /* STAT2 */
      Pico_mcd->s68k_regs[0x04+1] = 0x0f;
      return cdc.stat[2];

    case 0x0f:  /* STAT3 */
    {
      uint8 data = cdc.stat[3];

      /* clear !VALST (note: this is not 100% correct but BIOS do not seem to care) */
      cdc.stat[3] = BIT_VALST;

      /* clear pending decoder interrupt */
      cdc.ifstat |= BIT_DECI;
      
#if 0
      /* no pending data transfer end interrupt */
      if ((cdc.ifstat | BIT_DTEI) || !(cdc.ifctrl & BIT_DTEIEN))
      {
        /* clear pending level 5 interrupt */
        SekInterruptClearS68k(5);
      }
#endif

      Pico_mcd->s68k_regs[0x04+1] = 0x00;
      return data;
    }

    default:  /* by default, COMIN is always empty */
      return 0xff;
  }
}