#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct regstat {int /*<<< orphan*/  regmap; } ;
typedef  int /*<<< orphan*/  pointer ;

/* Variables and functions */
 int /*<<< orphan*/  CCREG ; 
 int CLOCK_DIVIDER ; 
 char HOST_CCREG ; 
 int /*<<< orphan*/  assert (int) ; 
 int* ccadj ; 
 int /*<<< orphan*/  emit_addimm (char,int,char) ; 
 int /*<<< orphan*/  emit_call (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_movimm (scalar_t__,int /*<<< orphan*/ ) ; 
 char get_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_delayslot ; 
 scalar_t__ master_handle_bios ; 
 scalar_t__ slave ; 
 scalar_t__ slave_handle_bios ; 
 scalar_t__ start ; 

void bios_assemble(int i,struct regstat *i_regs)
{
  signed char ccreg=get_reg(i_regs->regmap,CCREG);
  assert(ccreg==HOST_CCREG);
  assert(!is_delayslot);
  emit_movimm(start+i*2,0);
  //emit_writeword(0,slave?(int)&slave_pc:(int)&master_pc);
  emit_addimm(HOST_CCREG,CLOCK_DIVIDER*ccadj[i],HOST_CCREG);
  if(slave)
    emit_call((pointer)slave_handle_bios); // Probably doesn't work
  else
    emit_call((pointer)master_handle_bios);
}