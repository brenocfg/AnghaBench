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
struct TYPE_4__ {int* s68k_regs; } ;
struct TYPE_3__ {int ifstat; unsigned char ifctrl; int dbc; int dac; int wa; unsigned char* stat; unsigned char* ctrl; int pt; int /*<<< orphan*/  dma_w; } ;

/* Variables and functions */
 unsigned char BIT_AUTORQ ; 
 unsigned char BIT_DECEN ; 
 int BIT_DECI ; 
 unsigned char BIT_DECIEN ; 
 unsigned char BIT_DOUTEN ; 
 int BIT_DTBSY ; 
 int BIT_DTEI ; 
 unsigned char BIT_DTEIEN ; 
 int BIT_DTEN ; 
 unsigned char BIT_FORMRQ ; 
 unsigned char BIT_MODRQ ; 
 int /*<<< orphan*/  EL_ANOMALY ; 
 int /*<<< orphan*/  EL_INTS ; 
 int /*<<< orphan*/  EL_STATUS ; 
 int PCDS_IEN5 ; 
 int /*<<< orphan*/  PCD_EVENT_DMA ; 
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  SekInterruptClearS68k (int) ; 
 int /*<<< orphan*/  SekInterruptS68k (int) ; 
 TYPE_1__ cdc ; 
 int /*<<< orphan*/  cdc_reset () ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  pcd_event_schedule_s68k (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcm_ram_dma_w ; 
 int /*<<< orphan*/  prg_ram_dma_w ; 
 int /*<<< orphan*/  word_ram_0_dma_w ; 
 int /*<<< orphan*/  word_ram_1_dma_w ; 
 int /*<<< orphan*/  word_ram_2M_dma_w ; 

void cdc_reg_w(unsigned char data)
{
#ifdef LOG_CDC
  elprintf(EL_STATUS, "CDC register %X write 0x%04x", Pico_mcd->s68k_regs[0x04+1] & 0x0F, data);
#endif
  switch (Pico_mcd->s68k_regs[0x04+1] & 0x0F)
  {
    case 0x01:  /* IFCTRL */
    {
      /* pending interrupts ? */
      if (((data & BIT_DTEIEN) && !(cdc.ifstat & BIT_DTEI)) ||
          ((data & BIT_DECIEN) && !(cdc.ifstat & BIT_DECI)))
      {
        /* level 5 interrupt enabled ? */
        if (Pico_mcd->s68k_regs[0x32+1] & PCDS_IEN5)
        {
          /* update IRQ level */
          elprintf(EL_INTS, "cdc pending irq 5");
          SekInterruptS68k(5);
        }
      }
      else // if (scd.pending & (1 << 5))
      {
        /* clear pending level 5 interrupts */
        SekInterruptClearS68k(5);
      }

      /* abort any data transfer if data output is disabled */
      if (!(data & BIT_DOUTEN))
      {
        /* clear !DTBSY and !DTEN */
        cdc.ifstat |= (BIT_DTBSY | BIT_DTEN);
      }

      cdc.ifctrl = data;
      Pico_mcd->s68k_regs[0x04+1] = 0x02;
      break;
    }

    case 0x02:  /* DBCL */
      cdc.dbc &= 0xff00;
      cdc.dbc |= data;
      Pico_mcd->s68k_regs[0x04+1] = 0x03;
      break;

    case 0x03:  /* DBCH */
      cdc.dbc &= 0x00ff;
      cdc.dbc |= data << 8;
      Pico_mcd->s68k_regs[0x04+1] = 0x04;
      break;

    case 0x04:  /* DACL */
      cdc.dac &= 0xff00;
      cdc.dac |= data;
      Pico_mcd->s68k_regs[0x04+1] = 0x05;
      break;

    case 0x05:  /* DACH */
      cdc.dac &= 0x00ff;
      cdc.dac |= data << 8;
      Pico_mcd->s68k_regs[0x04+1] = 0x06;
      break;

    case 0x06:  /* DTRG */
    {
      /* start data transfer if data output is enabled */
      if (cdc.ifctrl & BIT_DOUTEN)
      {
        /* set !DTBSY */
        cdc.ifstat &= ~BIT_DTBSY;

        /* clear DBCH bits 4-7 */
        cdc.dbc &= 0x0fff;

        /* clear EDT & DSR bits (SCD register $04) */
        Pico_mcd->s68k_regs[0x04+0] &= 0x07;

        cdc.dma_w = 0;

        /* setup data transfer destination */
        switch (Pico_mcd->s68k_regs[0x04+0] & 0x07)
        {
          case 2: /* MAIN-CPU host read */
          case 3: /* SUB-CPU host read */
          {
            /* set !DTEN */
            cdc.ifstat &= ~BIT_DTEN;

            /* set DSR bit (register $04) */
            Pico_mcd->s68k_regs[0x04+0] |= 0x40;
            break;
          }

          case 4: /* PCM RAM DMA */
          {
            cdc.dma_w = pcm_ram_dma_w;
            break;
          }

          case 5: /* PRG-RAM DMA */
          {
            cdc.dma_w = prg_ram_dma_w;
            break;
          }

          case 7: /* WORD-RAM DMA */
          {
            /* check memory mode */
            if (Pico_mcd->s68k_regs[0x02+1] & 0x04)
            {
              /* 1M mode */
              if (Pico_mcd->s68k_regs[0x02+1] & 0x01)
              {
                /* Word-RAM bank 0 is assigned to SUB-CPU */
                cdc.dma_w = word_ram_0_dma_w;
              }
              else
              {
                /* Word-RAM bank 1 is assigned to SUB-CPU */
                cdc.dma_w = word_ram_1_dma_w;
              }
            }
            else
            {
              /* 2M mode */
              if (Pico_mcd->s68k_regs[0x02+1] & 0x02)
              {
                /* only process DMA if Word-RAM is assigned to SUB-CPU */
                cdc.dma_w = word_ram_2M_dma_w;
              }
            }
            break;
          }

          default: /* invalid */
          {
            elprintf(EL_ANOMALY, "invalid CDC tranfer destination (%d)",
              Pico_mcd->s68k_regs[0x04+0] & 0x07);
            break;
          }
        }

        if (cdc.dma_w)
          pcd_event_schedule_s68k(PCD_EVENT_DMA, cdc.dbc / 2);
      }

      Pico_mcd->s68k_regs[0x04+1] = 0x07;
      break;
    }

    case 0x07:  /* DTACK */
    {
      /* clear pending data transfer end interrupt */
      cdc.ifstat |= BIT_DTEI;

      /* clear DBCH bits 4-7 */
      cdc.dbc &= 0x0fff;

#if 0
      /* no pending decoder interrupt ? */
      if ((cdc.ifstat | BIT_DECI) || !(cdc.ifctrl & BIT_DECIEN))
      {
        /* clear pending level 5 interrupt */
        SekInterruptClearS68k(5);
      }
#endif
      Pico_mcd->s68k_regs[0x04+1] = 0x08;
      break;
    }

    case 0x08:  /* WAL */
      cdc.wa &= 0xff00;
      cdc.wa |= data;
      Pico_mcd->s68k_regs[0x04+1] = 0x09;
      break;

    case 0x09:  /* WAH */
      cdc.wa &= 0x00ff;
      cdc.wa |= data << 8;
      Pico_mcd->s68k_regs[0x04+1] = 0x0a;
      break;

    case 0x0a:  /* CTRL0 */
    {
      /* set CRCOK bit only if decoding is enabled */
      cdc.stat[0] = data & BIT_DECEN;

      /* update decoding mode */
      if (data & BIT_AUTORQ)
      {
        /* set MODE bit according to CTRL1 register & clear FORM bit */
        cdc.stat[2] = cdc.ctrl[1] & BIT_MODRQ;
      }
      else 
      {
        /* set MODE & FORM bits according to CTRL1 register */
        cdc.stat[2] = cdc.ctrl[1] & (BIT_MODRQ | BIT_FORMRQ);
      }

      cdc.ctrl[0] = data;
      Pico_mcd->s68k_regs[0x04+1] = 0x0b;
      break;
    }

    case 0x0b:  /* CTRL1 */
    {
      /* update decoding mode */
      if (cdc.ctrl[0] & BIT_AUTORQ)
      {
        /* set MODE bit according to CTRL1 register & clear FORM bit */
        cdc.stat[2] = data & BIT_MODRQ;
      }
      else 
      {
        /* set MODE & FORM bits according to CTRL1 register */
        cdc.stat[2] = data & (BIT_MODRQ | BIT_FORMRQ);
      }

      cdc.ctrl[1] = data;
      Pico_mcd->s68k_regs[0x04+1] = 0x0c;
      break;
    }

    case 0x0c:  /* PTL */
      cdc.pt &= 0xff00;
      cdc.pt |= data;
      Pico_mcd->s68k_regs[0x04+1] = 0x0d;
      break;
  
    case 0x0d:  /* PTH */
      cdc.pt &= 0x00ff;
      cdc.pt |= data << 8;
      Pico_mcd->s68k_regs[0x04+1] = 0x0e;
      break;

    case 0x0e:  /* CTRL2 (unused) */
      Pico_mcd->s68k_regs[0x04+1] = 0x0f;
      break;

    case 0x0f:  /* RESET */
      cdc_reset();
      break;

    default:  /* by default, SBOUT is not used */
      break;
  }
}