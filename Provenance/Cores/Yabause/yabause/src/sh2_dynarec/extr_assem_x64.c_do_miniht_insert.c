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

/* Variables and functions */
 int /*<<< orphan*/  add_to_linker (int,int,int) ; 
 int /*<<< orphan*/  emit_movimm (int,int) ; 
 int /*<<< orphan*/  emit_writeword (int,int) ; 
 int /*<<< orphan*/  emit_writeword_imm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ ** mini_ht_master ; 
 int /*<<< orphan*/ ** mini_ht_slave ; 
 scalar_t__ out ; 
 scalar_t__ slave ; 

void do_miniht_insert(int return_address,int rt,int temp) {
  emit_movimm(return_address,rt); // PC into link register
  //emit_writeword_imm(return_address,(int)&mini_ht[(return_address&0xFF)>>8][0]);
  if(slave) emit_writeword(rt,(int)&mini_ht_slave[(return_address&0xFF)>>3][0]);
  else emit_writeword(rt,(int)&mini_ht_master[(return_address&0xFF)>>3][0]);
  add_to_linker((int)out,return_address,1);
  if(slave) emit_writeword_imm(0,(int)&mini_ht_slave[(return_address&0xFF)>>3][1]);
  else emit_writeword_imm(0,(int)&mini_ht_master[(return_address&0xFF)>>3][1]);
}