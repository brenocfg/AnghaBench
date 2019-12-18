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
 int /*<<< orphan*/  emit_andimm (int,int,int) ; 
 int /*<<< orphan*/  emit_orrmi_imm (int,int,int) ; 
 int /*<<< orphan*/  emit_orrne_imm (int,int,int) ; 
 int /*<<< orphan*/  emit_teq (int,int) ; 
 int /*<<< orphan*/  emit_testimm (int,int) ; 

void emit_div0s(int s1, int s2, int sr, int temp) {
  emit_andimm(sr,0xfe,sr);
  emit_testimm(s2,0x80000000);
  emit_orrne_imm(sr,0x100,sr);
  emit_testimm(s1,0x80000000);
  emit_orrne_imm(sr,0x200,sr);
  emit_teq(s1,s2);
  emit_orrmi_imm(sr,1,sr);
}