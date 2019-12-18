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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int uint16 ;
struct TYPE_4__ {int* s68k_regs; } ;
struct TYPE_3__ {int* ctrl; int* stat; int ifctrl; int pt; int wa; int /*<<< orphan*/ * ram; int /*<<< orphan*/  ifstat; int /*<<< orphan*/ ** head; } ;

/* Variables and functions */
 int BIT_DECEN ; 
 int /*<<< orphan*/  BIT_DECI ; 
 int BIT_DECIEN ; 
 int BIT_WRRQ ; 
 int /*<<< orphan*/  EL_INTS ; 
 int PCDS_IEN5 ; 
 TYPE_2__* Pico_mcd ; 
 int /*<<< orphan*/  SekInterruptS68k (int) ; 
 TYPE_1__ cdc ; 
 int /*<<< orphan*/  cdd_read_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  elprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int cdc_decoder_update(uint8 header[4])
{
  /* data decoding enabled ? */
  if (cdc.ctrl[0] & BIT_DECEN)
  {
    /* update HEAD registers */
    memcpy(cdc.head[0], header, sizeof(cdc.head[0]));

    /* set !VALST */
    cdc.stat[3] = 0x00;

    /* pending decoder interrupt */
    cdc.ifstat &= ~BIT_DECI;

    /* decoder interrupt enabled ? */
    if (cdc.ifctrl & BIT_DECIEN)
    {
      /* level 5 interrupt enabled ? */
      if (Pico_mcd->s68k_regs[0x32+1] & PCDS_IEN5)
      {
        /* update IRQ level */
        elprintf(EL_INTS, "cdc DEC irq 5");
        SekInterruptS68k(5);
      }
    }

    /* buffer RAM write enabled ? */
    if (cdc.ctrl[0] & BIT_WRRQ)
    {
      uint16 offset;

      /* increment block pointer  */
      cdc.pt += 2352;

      /* increment write address */
      cdc.wa += 2352;

      /* CDC buffer address */
      offset = cdc.pt & 0x3fff;

      /* write CDD block header (4 bytes) */
      memcpy(cdc.ram + offset, header, 4);

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