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
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void emit_negc(int rs, int rt, int sr)
{
assert(0);
/*
  assert(rs>=0&&rs<8);
  if(rt<0) {
    emit_shrimm(sr,1,sr); // Get C flag
    emit_jc((int)out+10); // 6
    emit_neg(rs,rs); // 2
    emit_neg(rs,rs); // 2
    emit_adc(sr,sr); // Save C flag
  }else{
    if(rs!=rt) emit_mov(rs,rt);
    emit_shrimm(sr,1,sr); // Get C flag
    emit_jc((int)out+9); // 6
    emit_addimm(rt,-1,rt); // 3
    emit_adc(sr,sr); // Save C flag
    emit_not(rt,rt);
  }
*/
}