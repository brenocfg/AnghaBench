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
 int /*<<< orphan*/  CC_STUB ; 
 scalar_t__ CJUMP ; 
 int CLOCK_DIVIDER ; 
 int /*<<< orphan*/  HOST_CCREG ; 
 int NODS ; 
 scalar_t__ RJUMP ; 
 scalar_t__ SJUMP ; 
 int TAKEN ; 
 int /*<<< orphan*/  add_stub (int /*<<< orphan*/ ,int,int,int,int,int,int,int /*<<< orphan*/ ) ; 
 int* ba ; 
 int* ccadj ; 
 int* cycles ; 
 int /*<<< orphan*/  emit_addimm_and_set_flags (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_andimm (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_cmpimm (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_jmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_jns (int /*<<< orphan*/ ) ; 
 scalar_t__ internal_branch (int) ; 
 scalar_t__* is_ds ; 
 scalar_t__* itype ; 
 scalar_t__ out ; 
 scalar_t__* source ; 
 int start ; 

void do_cc(int i,signed char i_regmap[],int *adj,int addr,int taken,int invert)
{
  int count;
  int jaddr;
  int idle=0;
  if(itype[i]==RJUMP)
  {
    *adj=0;
  }
  //if(ba[i]>=start && ba[i]<(start+slen*4))
  if(internal_branch(ba[i]))
  {
    int t=(ba[i]-start)>>1;
    if(is_ds[t]) *adj=ccadj[t+1]-cycles[t]; // Branch into delay slot adds an extra cycle
    else *adj=ccadj[t];
  }
  else
  {
    *adj=0;
  }
  if(itype[i]==CJUMP) *adj-=2+cycles[i]; // Two extra cycles for taken BT/BF
  if(itype[i]==SJUMP) *adj-=1+cycles[i]+cycles[i+1]; // One extra cycle for taken BT/BF with delay slot
  count=ccadj[i]+((taken==NODS)?0:cycles[i]+cycles[i+1]);
  if(taken==TAKEN && i==(ba[i]-start)>>1 && source[i+1]==0) {
    // Idle loop
    // FIXME
    //if(count&1) emit_addimm_and_set_flags(2*(count+2),HOST_CCREG);
    idle=(int)out;
    //emit_subfrommem(&idlecount,HOST_CCREG); // Count idle cycles
    emit_andimm(HOST_CCREG,3,HOST_CCREG);
    jaddr=(int)out;
    emit_jmp(0);
  }
  else if(*adj==0||invert) {
    emit_addimm_and_set_flags(CLOCK_DIVIDER*count,HOST_CCREG);
    jaddr=(int)out;
    emit_jns(0);
  }
  else
  {
    emit_cmpimm(HOST_CCREG,-CLOCK_DIVIDER*count);
    jaddr=(int)out;
    emit_jns(0);
  }
  add_stub(CC_STUB,jaddr,idle?idle:(int)out,(*adj==0||invert||idle)?0:count,i,addr,taken,0);
}