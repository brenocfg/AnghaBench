#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned short u32 ;
struct TYPE_12__ {scalar_t__ rom; } ;
struct TYPE_11__ {int v; } ;
struct TYPE_7__ {int* RAM1; } ;
struct TYPE_8__ {TYPE_1__ bank; } ;
struct TYPE_10__ {int emu_status; int** pmac; TYPE_2__ mem; } ;
struct TYPE_9__ {scalar_t__ iram_rom; scalar_t__ dram; } ;

/* Variables and functions */
 int CADDR ; 
 int EL_ANOMALY ; 
 int EL_SVP ; 
 int GET_PPC_OFFS () ; 
 int* PC ; 
 int SSP_PMC_HAVE_ADDR ; 
 int SSP_PMC_SET ; 
 TYPE_6__ cart ; 
 int /*<<< orphan*/  elprintf (int,char*,int,...) ; 
 int get_inc (int) ; 
 int last_iram ; 
 int /*<<< orphan*/  overwite_write (unsigned short,unsigned short) ; 
 TYPE_5__ rPMC ; 
 int rST ; 
 TYPE_4__* ssp ; 
 TYPE_3__* svp ; 

__attribute__((used)) static u32 pm_io(int reg, int write, u32 d)
{
  if (ssp->emu_status & SSP_PMC_SET)
  {
    /* this MUST be blind r or w */
    if ((*(PC-1) & 0xff0f) && (*(PC-1) & 0xfff0)) {
#ifdef LOG_SVP
      elprintf(EL_SVP|EL_ANOMALY, "ssp FIXME: tried to set PM%i (%c) with non-blind i/o %08x @ %04x",
        reg, write ? 'w' : 'r', rPMC.v, GET_PPC_OFFS());
#endif
      ssp->emu_status &= ~SSP_PMC_SET;
      return 0;
    }
#ifdef LOG_SVP
    elprintf(EL_SVP, "PM%i (%c) set to %08x @ %04x", reg, write ? 'w' : 'r', rPMC.v, GET_PPC_OFFS());
#endif
    ssp->pmac[write][reg] = rPMC.v;
    ssp->emu_status &= ~SSP_PMC_SET;
#ifdef LOG_SVP
    if ((rPMC.v & 0x7f) == 0x1c && (rPMC.v & 0x7fff0000) == 0) {
      elprintf(EL_SVP, "ssp IRAM copy from %06x", (ssp->mem.bank.RAM1[0]-1)<<1);
#ifdef USE_DEBUGGER
      last_iram = (ssp->mem.bank.RAM1[0]-1)<<1;
#endif
    }
#endif
    return 0;
  }

  /* just in case */
  if (ssp->emu_status & SSP_PMC_HAVE_ADDR) {
#ifdef LOG_SVP
    elprintf(EL_SVP|EL_ANOMALY, "ssp FIXME: PM%i (%c) with only addr set @ %04x",
      reg, write ? 'w' : 'r', GET_PPC_OFFS());
#endif
    ssp->emu_status &= ~SSP_PMC_HAVE_ADDR;
  }

  if (reg == 4 || (rST & 0x60))
  {
#ifdef LOG_SVP
    #define CADDR ((((mode<<16)&0x7f0000)|addr)<<1)
#endif
    unsigned short *dram = (unsigned short *)svp->dram;
    if (write)
    {
      /*int mode = ssp->pmac_write[reg]&0xffff;
      int addr = ssp->pmac_write[reg]>>16;*/
      int addr = ssp->pmac[1][reg]&0xffff;
      int mode = ssp->pmac[1][reg]>>16;
#ifdef LOG_SVP
      if ((mode & 0xb800) == 0xb800)
        elprintf(EL_SVP|EL_ANOMALY, "ssp FIXME: mode %04x", mode);
#endif
      if ((mode & 0x43ff) == 0x0018) /* DRAM */
      {
        int inc = get_inc(mode);
#ifdef LOG_SVP
        elprintf(EL_SVP, "ssp PM%i DRAM w [%06x] %04x (inc %i, ovrw %i)",
          reg, CADDR, d, inc >> 16, (mode>>10)&1);
#endif
        if (mode & 0x0400) {
               overwite_write(dram[addr], d);
        } else dram[addr] = d;
        ssp->pmac[1][reg] += inc;
      }
      else if ((mode & 0xfbff) == 0x4018) /* DRAM, cell inc */
      {
#ifdef LOG_SVP
        elprintf(EL_SVP, "ssp PM%i DRAM w [%06x] %04x (cell inc, ovrw %i) @ %04x",
          reg, CADDR, d, (mode>>10)&1, GET_PPC_OFFS());
#endif
        if (mode & 0x0400) {
               overwite_write(dram[addr], d);
        } else dram[addr] = d;
        /* ssp->pmac_write[reg] += (addr&1) ? (31<<16) : (1<<16); */
        ssp->pmac[1][reg] += (addr&1) ? 31 : 1;
      }
      else if ((mode & 0x47ff) == 0x001c) /* IRAM */
      {
        int inc = get_inc(mode);
#ifdef LOG_SVP
        if ((addr&0xfc00) != 0x8000)
          elprintf(EL_SVP|EL_ANOMALY, "ssp FIXME: invalid IRAM addr: %04x", addr<<1);
        elprintf(EL_SVP, "ssp IRAM w [%06x] %04x (inc %i)", (addr<<1)&0x7ff, d, inc >> 16);
#endif
        ((unsigned short *)svp->iram_rom)[addr&0x3ff] = d;
        ssp->pmac[1][reg] += inc;
      }
#ifdef LOG_SVP
      else
      {
        elprintf(EL_SVP|EL_ANOMALY, "ssp FIXME: PM%i unhandled write mode %04x, [%06x] %04x @ %04x",
            reg, mode, CADDR, d, GET_PPC_OFFS());
      }
#endif
    }
    else
    {
      /*int mode = ssp->pmac_read[reg]&0xffff;
      int addr = ssp->pmac_read[reg]>>16;*/
      int addr = ssp->pmac[0][reg]&0xffff;
      int mode = ssp->pmac[0][reg]>>16;

      if      ((mode & 0xfff0) == 0x0800) /* ROM, inc 1, verified to be correct */
      {
#ifdef LOG_SVP
        elprintf(EL_SVP, "ssp ROM  r [%06x] %04x", CADDR,
          ((unsigned short *)cart.rom)[addr|((mode&0xf)<<16)]);
#endif
        /*if ((signed int)ssp->pmac_read[reg] >> 16 == -1) ssp->pmac_read[reg]++;
        ssp->pmac_read[reg] += 1<<16;*/
        if ((signed int)(ssp->pmac[0][reg] & 0xffff) == -1) ssp->pmac[0][reg] += 1<<16;
        ssp->pmac[0][reg] ++;
        
        d = ((unsigned short *)cart.rom)[addr|((mode&0xf)<<16)];
      }
      else if ((mode & 0x47ff) == 0x0018) /* DRAM */
      {
        int inc = get_inc(mode);
#ifdef LOG_SVP
        elprintf(EL_SVP, "ssp PM%i DRAM r [%06x] %04x (inc %i)", reg, CADDR, dram[addr], inc >> 16);
#endif
        d = dram[addr];
        ssp->pmac[0][reg] += inc;
      }
      else
      {
#ifdef LOG_SVP
        elprintf(EL_SVP|EL_ANOMALY, "ssp FIXME: PM%i unhandled read  mode %04x, [%06x] @ %04x",
            reg, mode, CADDR, GET_PPC_OFFS());
#endif
        d = 0;
      }
    }

    /* PMC value corresponds to last PMR accessed (not sure). */
    rPMC.v = ssp->pmac[write][reg];

    return d;
  }

  return (u32)-1;
}