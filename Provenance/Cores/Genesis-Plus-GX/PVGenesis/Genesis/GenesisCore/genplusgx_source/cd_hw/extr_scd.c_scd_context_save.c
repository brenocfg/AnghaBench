#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8 ;
struct TYPE_12__ {int l; } ;
struct TYPE_15__ {TYPE_1__ byte; } ;
typedef  TYPE_4__ uint32 ;
typedef  TYPE_4__ uint16 ;
struct TYPE_17__ {TYPE_4__ stopped; TYPE_4__ int_level; TYPE_4__ cycles; TYPE_4__ poll; } ;
struct TYPE_14__ {scalar_t__ boot; } ;
struct TYPE_16__ {TYPE_3__ cartridge; TYPE_4__* word_ram_2M; TYPE_4__* word_ram; TYPE_4__* regs; TYPE_4__* prg_ram; TYPE_4__ dmna; TYPE_4__ pending; TYPE_4__ timer; TYPE_4__ cycles; } ;
struct TYPE_13__ {scalar_t__ base; } ;
struct TYPE_11__ {TYPE_2__* memory_map; TYPE_4__ poll; } ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_REG_A0 ; 
 int /*<<< orphan*/  M68K_REG_A1 ; 
 int /*<<< orphan*/  M68K_REG_A2 ; 
 int /*<<< orphan*/  M68K_REG_A3 ; 
 int /*<<< orphan*/  M68K_REG_A4 ; 
 int /*<<< orphan*/  M68K_REG_A5 ; 
 int /*<<< orphan*/  M68K_REG_A6 ; 
 int /*<<< orphan*/  M68K_REG_A7 ; 
 int /*<<< orphan*/  M68K_REG_D0 ; 
 int /*<<< orphan*/  M68K_REG_D1 ; 
 int /*<<< orphan*/  M68K_REG_D2 ; 
 int /*<<< orphan*/  M68K_REG_D3 ; 
 int /*<<< orphan*/  M68K_REG_D4 ; 
 int /*<<< orphan*/  M68K_REG_D5 ; 
 int /*<<< orphan*/  M68K_REG_D6 ; 
 int /*<<< orphan*/  M68K_REG_D7 ; 
 int /*<<< orphan*/  M68K_REG_ISP ; 
 int /*<<< orphan*/  M68K_REG_PC ; 
 int /*<<< orphan*/  M68K_REG_SR ; 
 int /*<<< orphan*/  M68K_REG_USP ; 
 scalar_t__ cdc_context_save (int /*<<< orphan*/ *) ; 
 scalar_t__ cdd_context_save (int /*<<< orphan*/ *) ; 
 scalar_t__ gfx_context_save (int /*<<< orphan*/ *) ; 
 TYPE_10__ m68k ; 
 scalar_t__ md_cart_context_save (int /*<<< orphan*/ *) ; 
 scalar_t__ pcm_context_save (int /*<<< orphan*/ *) ; 
 TYPE_9__ s68k ; 
 TYPE_4__ s68k_get_reg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_param (TYPE_4__*,int) ; 
 TYPE_6__ scd ; 

int scd_context_save(uint8 *state)
{
  uint16 tmp16;
  uint32 tmp32;
  int bufferptr = 0;

  /* internal harware */
  save_param(scd.regs, sizeof(scd.regs));
  save_param(&scd.cycles, sizeof(scd.cycles));
  save_param(&scd.timer, sizeof(scd.timer));
  save_param(&scd.pending, sizeof(scd.pending));
  save_param(&scd.dmna, sizeof(scd.dmna));

  /* GFX processor */
  bufferptr += gfx_context_save(&state[bufferptr]);

  /* CD Data controller */
  bufferptr += cdc_context_save(&state[bufferptr]);

  /* CD Drive processor */
  bufferptr += cdd_context_save(&state[bufferptr]);

  /* PCM chip */
  bufferptr += pcm_context_save(&state[bufferptr]);

  /* PRG-RAM */
  save_param(scd.prg_ram, sizeof(scd.prg_ram));

  /* Word-RAM */
  if (scd.regs[0x03>>1].byte.l & 0x04)
  {
    /* 1M mode */
    save_param(scd.word_ram, sizeof(scd.word_ram));
  }
  else
  {
    /* 2M mode */
    save_param(scd.word_ram_2M, sizeof(scd.word_ram_2M));
  }

  /* MAIN-CPU & SUB-CPU polling */
  save_param(&m68k.poll, sizeof(m68k.poll));
  save_param(&s68k.poll, sizeof(s68k.poll));

  /* H-INT default vector */
  tmp16 = *(uint16 *)(m68k.memory_map[0].base + 0x72);
  save_param(&tmp16, 2);

  /* SUB-CPU internal state */
  save_param(&s68k.cycles, sizeof(s68k.cycles));
  save_param(&s68k.int_level, sizeof(s68k.int_level));
  save_param(&s68k.stopped, sizeof(s68k.stopped));

  /* SUB-CPU registers */
  tmp32 = s68k_get_reg(M68K_REG_D0);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_D1);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_D2);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_D3);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_D4);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_D5);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_D6);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_D7);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_A0);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_A1);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_A2);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_A3);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_A4);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_A5);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_A6);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_A7);  save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_PC);  save_param(&tmp32, 4);
  tmp16 = s68k_get_reg(M68K_REG_SR);  save_param(&tmp16, 2); 
  tmp32 = s68k_get_reg(M68K_REG_USP); save_param(&tmp32, 4);
  tmp32 = s68k_get_reg(M68K_REG_ISP); save_param(&tmp32, 4);

  /* bootable MD cartridge */
  if (scd.cartridge.boot)
  {
    bufferptr += md_cart_context_save(&state[bufferptr]);
  }

  return bufferptr;
}