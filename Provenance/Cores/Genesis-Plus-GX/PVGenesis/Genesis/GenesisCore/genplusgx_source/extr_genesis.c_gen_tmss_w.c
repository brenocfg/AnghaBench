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
struct TYPE_6__ {TYPE_1__* memory_map; } ;
struct TYPE_5__ {int /*<<< orphan*/  write; int /*<<< orphan*/  read; } ;
struct TYPE_4__ {int /*<<< orphan*/  write16; int /*<<< orphan*/  write8; int /*<<< orphan*/  read16; int /*<<< orphan*/  read8; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_WORD (scalar_t__,unsigned int,unsigned int) ; 
 TYPE_3__ m68k ; 
 int /*<<< orphan*/  m68k_lockup_r_16 ; 
 int /*<<< orphan*/  m68k_lockup_r_8 ; 
 int /*<<< orphan*/  m68k_lockup_w_16 ; 
 int /*<<< orphan*/  m68k_lockup_w_8 ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 scalar_t__ tmss ; 
 int /*<<< orphan*/  vdp_read_byte ; 
 int /*<<< orphan*/  vdp_read_word ; 
 int /*<<< orphan*/  vdp_write_byte ; 
 int /*<<< orphan*/  vdp_write_word ; 
 int /*<<< orphan*/  zbank_lockup_r ; 
 int /*<<< orphan*/  zbank_lockup_w ; 
 TYPE_2__* zbank_memory_map ; 
 int /*<<< orphan*/  zbank_read_vdp ; 
 int /*<<< orphan*/  zbank_write_vdp ; 

void gen_tmss_w(unsigned int offset, unsigned int data)
{
  int i;

  /* write TMSS register */
  WRITE_WORD(tmss, offset, data);

  /* VDP requires "SEGA" value to be written in TMSS register */
  if (memcmp((char *)tmss, "SEGA", 4) == 0)
  {
    for (i=0xc0; i<0xe0; i+=8)
    {
      m68k.memory_map[i].read8    = vdp_read_byte;
      m68k.memory_map[i].read16   = vdp_read_word;
      m68k.memory_map[i].write8   = vdp_write_byte;
      m68k.memory_map[i].write16  = vdp_write_word;
      zbank_memory_map[i].read    = zbank_read_vdp;
      zbank_memory_map[i].write   = zbank_write_vdp;
    }
  }
  else
  {
    for (i=0xc0; i<0xe0; i+=8)
    {
      m68k.memory_map[i].read8    = m68k_lockup_r_8;
      m68k.memory_map[i].read16   = m68k_lockup_r_16;
      m68k.memory_map[i].write8   = m68k_lockup_w_8;
      m68k.memory_map[i].write16  = m68k_lockup_w_16;
      zbank_memory_map[i].read    = zbank_lockup_r;
      zbank_memory_map[i].write   = zbank_lockup_w;
    }
  }
}