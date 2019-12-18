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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  emit_adc (int,int) ; 
 int /*<<< orphan*/  emit_adcimm (int,int) ; 
 int /*<<< orphan*/  emit_addimm_and_set_flags (int,int) ; 
 int /*<<< orphan*/  emit_andimm (int,int,int) ; 
 int /*<<< orphan*/  emit_mov (int,int) ; 
 int /*<<< orphan*/  emit_not (int,int) ; 
 int /*<<< orphan*/  emit_popreg (int) ; 
 int /*<<< orphan*/  emit_pushreg (int) ; 
 int /*<<< orphan*/  emit_shrimm (int,int,int) ; 
 int /*<<< orphan*/  emit_xor (int,int,int) ; 

void emit_cmpstr(int s1, int s2, int sr, int temp)
{
  // Compare s1 and s2.  If any byte is equal, set T.
  // Calculates the xor of the strings, then checks if any byte is
  // zero by subtracting 1 from each byte.  If there is a carry/borrow
  // then a byte was zero.
  assert(temp>=0);
  emit_pushreg(s2);
  emit_xor(s1,s2,s2);
  emit_shrimm(sr,1,sr);
  emit_mov(s2,temp);
  emit_addimm_and_set_flags(0-0x01010101,temp);
  emit_adcimm(-1,temp);
  emit_not(s2,s2);
  emit_xor(temp,s2,temp);
  emit_andimm(temp,0x01010101,temp);
  emit_addimm_and_set_flags(-1,temp);
  emit_adc(sr,sr);
  emit_popreg(s2);
}