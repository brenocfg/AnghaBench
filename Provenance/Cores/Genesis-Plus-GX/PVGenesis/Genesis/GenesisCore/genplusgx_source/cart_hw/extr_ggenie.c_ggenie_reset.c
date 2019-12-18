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
struct TYPE_6__ {int /*<<< orphan*/  rom; int /*<<< orphan*/  addr; int /*<<< orphan*/  data; int /*<<< orphan*/  old; int /*<<< orphan*/  regs; scalar_t__ enabled; } ;
struct TYPE_5__ {TYPE_1__* memory_map; } ;
struct TYPE_4__ {int /*<<< orphan*/ * read16; int /*<<< orphan*/  write16; int /*<<< orphan*/  write8; int /*<<< orphan*/  base; } ;

/* Variables and functions */
 TYPE_3__ ggenie ; 
 int /*<<< orphan*/  ggenie_switch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ggenie_write_byte ; 
 int /*<<< orphan*/  ggenie_write_word ; 
 TYPE_2__ m68k ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void ggenie_reset(int hard)
{
  if (ggenie.enabled)
  {
    if (hard)
    {
      /* clear codes */
      ggenie_switch(0);

      /* reset internal state */
      memset(ggenie.regs,0,sizeof(ggenie.regs));
      memset(ggenie.old,0,sizeof(ggenie.old));
      memset(ggenie.data,0,sizeof(ggenie.data));
      memset(ggenie.addr,0,sizeof(ggenie.addr));
    }

    /* Game Genie ROM is mapped at $000000-$007fff */
    m68k.memory_map[0].base = ggenie.rom;

    /* Internal registers are mapped at $000000-$00001f */
    m68k.memory_map[0].write8   = ggenie_write_byte;
    m68k.memory_map[0].write16  = ggenie_write_word;

    /* Disable registers reads */
    m68k.memory_map[0].read16 = NULL;
  }
}