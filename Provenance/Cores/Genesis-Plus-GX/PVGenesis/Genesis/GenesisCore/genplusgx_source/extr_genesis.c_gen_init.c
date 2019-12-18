#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  addr_error; } ;
struct TYPE_7__ {TYPE_1__* memory_map; int /*<<< orphan*/  aerr_enabled; } ;
struct TYPE_6__ {int /*<<< orphan*/ * write; int /*<<< orphan*/  read; } ;
struct TYPE_5__ {int /*<<< orphan*/ * write16; int /*<<< orphan*/ * write8; int /*<<< orphan*/ * read16; int /*<<< orphan*/ * read8; void* base; } ;

/* Variables and functions */
#define  SYSTEM_GG 134 
#define  SYSTEM_GGMS 133 
#define  SYSTEM_MARKIII 132 
 int SYSTEM_MCD ; 
 int SYSTEM_MD ; 
#define  SYSTEM_PBC 131 
 int SYSTEM_PICO ; 
#define  SYSTEM_SG 130 
#define  SYSTEM_SMS 129 
#define  SYSTEM_SMS2 128 
 TYPE_4__ config ; 
 int /*<<< orphan*/ * ctrl_io_read_byte ; 
 int /*<<< orphan*/ * ctrl_io_read_word ; 
 int /*<<< orphan*/ * ctrl_io_write_byte ; 
 int /*<<< orphan*/ * ctrl_io_write_word ; 
 TYPE_3__ m68k ; 
 int /*<<< orphan*/  m68k_init () ; 
 int /*<<< orphan*/ * m68k_lockup_r_16 ; 
 int /*<<< orphan*/ * m68k_lockup_r_8 ; 
 int /*<<< orphan*/ * m68k_lockup_w_16 ; 
 int /*<<< orphan*/ * m68k_lockup_w_8 ; 
 int /*<<< orphan*/ * m68k_read_bus_16 ; 
 int /*<<< orphan*/ * m68k_read_bus_8 ; 
 void* m68k_unused_16_w ; 
 void* m68k_unused_8_w ; 
 int /*<<< orphan*/  md_cart_init () ; 
 scalar_t__ pico_current ; 
 int /*<<< orphan*/ * pico_read_byte ; 
 int /*<<< orphan*/ * pico_read_word ; 
 int /*<<< orphan*/  s68k_init () ; 
 int /*<<< orphan*/  scd_init () ; 
 int /*<<< orphan*/  sms_cart_init () ; 
 int system_hw ; 
 int /*<<< orphan*/ * vdp_read_byte ; 
 int /*<<< orphan*/ * vdp_read_word ; 
 int /*<<< orphan*/ * vdp_write_byte ; 
 int /*<<< orphan*/ * vdp_write_word ; 
 void* work_ram ; 
 int /*<<< orphan*/  z80_gg_port_r ; 
 int /*<<< orphan*/  z80_gg_port_w ; 
 int /*<<< orphan*/  z80_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  z80_irq_callback ; 
 int /*<<< orphan*/  z80_m3_port_r ; 
 int /*<<< orphan*/  z80_m3_port_w ; 
 int /*<<< orphan*/  z80_md_port_r ; 
 int /*<<< orphan*/  z80_md_port_w ; 
 int /*<<< orphan*/  z80_memory_r ; 
 int /*<<< orphan*/  z80_memory_w ; 
 int /*<<< orphan*/  z80_ms_port_r ; 
 int /*<<< orphan*/  z80_ms_port_w ; 
 int /*<<< orphan*/ ** z80_readmap ; 
 int /*<<< orphan*/  z80_readmem ; 
 int /*<<< orphan*/  z80_readport ; 
 int /*<<< orphan*/  z80_sg_port_r ; 
 int /*<<< orphan*/  z80_sg_port_w ; 
 int /*<<< orphan*/  z80_unused_port_r ; 
 int /*<<< orphan*/  z80_unused_port_w ; 
 int /*<<< orphan*/  z80_writemem ; 
 int /*<<< orphan*/  z80_writeport ; 
 int /*<<< orphan*/  zbank_lockup_r ; 
 int /*<<< orphan*/ * zbank_lockup_w ; 
 TYPE_2__* zbank_memory_map ; 
 int /*<<< orphan*/  zbank_read_ctrl_io ; 
 int /*<<< orphan*/  zbank_read_vdp ; 
 int /*<<< orphan*/  zbank_unused_r ; 
 int /*<<< orphan*/ * zbank_write_ctrl_io ; 
 int /*<<< orphan*/ * zbank_write_vdp ; 
 int /*<<< orphan*/ * zram ; 

void gen_init(void)
{
  int i;

  /* initialize Z80 */
  z80_init(0,z80_irq_callback);

  /* 8-bit / 16-bit modes */
  if ((system_hw & SYSTEM_PBC) == SYSTEM_MD)
  {
    /* initialize main 68k */
    m68k_init();
    m68k.aerr_enabled = config.addr_error; 

    /* initialize main 68k memory map */

    /* $800000-$DFFFFF : illegal access by default */
    for (i=0x80; i<0xe0; i++)
    {
      m68k.memory_map[i].base     = work_ram; /* for VDP DMA */
      m68k.memory_map[i].read8    = m68k_lockup_r_8;
      m68k.memory_map[i].read16   = m68k_lockup_r_16;
      m68k.memory_map[i].write8   = m68k_lockup_w_8;
      m68k.memory_map[i].write16  = m68k_lockup_w_16;
      zbank_memory_map[i].read    = zbank_lockup_r;
      zbank_memory_map[i].write   = zbank_lockup_w;
    }

    /* $C0xxxx, $C8xxxx, $D0xxxx, $D8xxxx : VDP ports */
    for (i=0xc0; i<0xe0; i+=8)
    {
      m68k.memory_map[i].read8    = vdp_read_byte;
      m68k.memory_map[i].read16   = vdp_read_word;
      m68k.memory_map[i].write8   = vdp_write_byte;
      m68k.memory_map[i].write16  = vdp_write_word;
      zbank_memory_map[i].read    = zbank_read_vdp;
      zbank_memory_map[i].write   = zbank_write_vdp;
    }

    /* $E00000-$FFFFFF : Work RAM (64k) */
    for (i=0xe0; i<0x100; i++)
    {
      m68k.memory_map[i].base     = work_ram;
      m68k.memory_map[i].read8    = NULL;
      m68k.memory_map[i].read16   = NULL;
      m68k.memory_map[i].write8   = NULL;
      m68k.memory_map[i].write16  = NULL;

      /* Z80 can ONLY write to 68k RAM, not read it */
      zbank_memory_map[i].read    = zbank_unused_r; 
      zbank_memory_map[i].write   = NULL;
    }

    if (system_hw == SYSTEM_PICO)
    {
      /* additional registers mapped to $800000-$80FFFF */
      m68k.memory_map[0x80].read8   = pico_read_byte;
      m68k.memory_map[0x80].read16  = pico_read_word;
      m68k.memory_map[0x80].write8  = m68k_unused_8_w;
      m68k.memory_map[0x80].write16 = m68k_unused_16_w;

      /* there is no I/O area (Notaz) */
      m68k.memory_map[0xa1].read8   = m68k_read_bus_8;
      m68k.memory_map[0xa1].read16  = m68k_read_bus_16;
      m68k.memory_map[0xa1].write8  = m68k_unused_8_w;
      m68k.memory_map[0xa1].write16 = m68k_unused_16_w;

      /* initialize page index (closed) */
      pico_current = 0;
    }
    else
    {
      /* $A10000-$A1FFFF : I/O & Control registers */
      m68k.memory_map[0xa1].read8   = ctrl_io_read_byte;
      m68k.memory_map[0xa1].read16  = ctrl_io_read_word;
      m68k.memory_map[0xa1].write8  = ctrl_io_write_byte;
      m68k.memory_map[0xa1].write16 = ctrl_io_write_word;
      zbank_memory_map[0xa1].read   = zbank_read_ctrl_io;
      zbank_memory_map[0xa1].write  = zbank_write_ctrl_io;

      /* initialize Z80 memory map */
      /* $0000-$3FFF is mapped to Z80 RAM (8K mirrored) */
      /* $4000-$FFFF is mapped to hardware but Z80 PC should never point there */
      for (i=0; i<64; i++)
      {
        z80_readmap[i] = &zram[(i & 7) << 10];
      }

      /* initialize Z80 memory handlers */
      z80_writemem  = z80_memory_w;
      z80_readmem   = z80_memory_r;

      /* initialize Z80 port handlers */
      z80_writeport = z80_unused_port_w;
      z80_readport  = z80_unused_port_r;
    }

    /* $000000-$7FFFFF : external hardware area */
    if (system_hw == SYSTEM_MCD)
    {
      /* initialize SUB-CPU */
      s68k_init();

      /* initialize CD hardware */
      scd_init();
    }
    else
    {
      /* Cartridge hardware */
      md_cart_init();
    }
  }
  else
  {
    /* initialize cartridge hardware & Z80 memory handlers */
    sms_cart_init();

    /* initialize Z80 ports handlers */
    switch (system_hw)
    {
      /* Master System compatibility mode */
      case SYSTEM_PBC:
      {
        z80_writeport = z80_md_port_w;
        z80_readport  = z80_md_port_r;
        break;
      }

      /* Game Gear hardware */
      case SYSTEM_GG:
      case SYSTEM_GGMS:
      {
        /* initialize cartridge hardware & Z80 memory handlers */
        sms_cart_init();

        /* initialize Z80 ports handlers */
        z80_writeport = z80_gg_port_w;
        z80_readport  = z80_gg_port_r;
        break;
      }

      /* Master SYstem hardware */
      case SYSTEM_SMS:
      case SYSTEM_SMS2:
      {
        z80_writeport = z80_ms_port_w;
        z80_readport  = z80_ms_port_r;
        break;
      }

      /* Mark-III hardware */
      case SYSTEM_MARKIII:
      {
        z80_writeport = z80_m3_port_w;
        z80_readport  = z80_m3_port_r;
        break;
      }

      /* SG-1000 hardware */
      case SYSTEM_SG:
      {
        z80_writeport = z80_sg_port_w;
        z80_readport  = z80_sg_port_r;
        break;
      }
    }
  }
}