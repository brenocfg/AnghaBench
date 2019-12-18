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
typedef  int /*<<< orphan*/  uint32 ;
typedef  int uint16 ;
struct TYPE_10__ {int w; } ;
struct TYPE_9__ {int w; } ;
struct TYPE_12__ {int* ctrl; int* stat; int ifctrl; scalar_t__ ram; TYPE_4__ pt; TYPE_3__ wa; int /*<<< orphan*/  ifstat; scalar_t__* head; } ;
struct TYPE_11__ {int pending; TYPE_2__* regs; } ;
struct TYPE_7__ {int l; } ;
struct TYPE_8__ {TYPE_1__ byte; } ;

/* Variables and functions */
 int BIT_DECEN ; 
 int /*<<< orphan*/  BIT_DECI ; 
 int BIT_DECIEN ; 
 int BIT_WRRQ ; 
 TYPE_6__ cdc ; 
 int /*<<< orphan*/  cdd_read_data (scalar_t__) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  s68k_update_irq (int) ; 
 TYPE_5__ scd ; 

int cdc_decoder_update(uint32 header)
{
  /* data decoding enabled ? */
  if (cdc.ctrl[0] & BIT_DECEN)
  {
    /* update HEAD registers */
    *(uint32 *)(cdc.head[0]) = header;

    /* set !VALST */
    cdc.stat[3] = 0x00;

    /* pending decoder interrupt */
    cdc.ifstat &= ~BIT_DECI;

    /* decoder interrupt enabled ? */
    if (cdc.ifctrl & BIT_DECIEN)
    {
      /* pending level 5 interrupt */
      scd.pending |= (1 << 5);

      /* level 5 interrupt enabled ? */
      if (scd.regs[0x32>>1].byte.l & 0x20)
      {
        /* update IRQ level */
        s68k_update_irq((scd.pending & scd.regs[0x32>>1].byte.l) >> 1);
      }
    }

    /* buffer RAM write enabled ? */
    if (cdc.ctrl[0] & BIT_WRRQ)
    {
      uint16 offset;

      /* increment block pointer  */
      cdc.pt.w += 2352;

      /* increment write address */
      cdc.wa.w += 2352;

      /* CDC buffer address */
      offset = cdc.pt.w & 0x3fff;

      /* write CDD block header (4 bytes) */
      *(uint32 *)(cdc.ram + offset) = header;

      /* write CDD block data (2048 bytes) */
      cdd_read_data(cdc.ram + 4 + offset);

      /* take care of buffer overrun */
      if (offset > (0x4000 - 2048 - 4))
      {
        /* data should be written at the start of buffer */
        memcpy(cdc.ram, cdc.ram + 0x4000, offset + 2048 + 4 - 0x4000);
      }

      /* read next data block */
      return 1;
    }
  }
  
  /* keep decoding same data block if Buffer Write is disabled */
  return 0;
}