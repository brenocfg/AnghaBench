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
 int /*<<< orphan*/  emit_addimm_and_set_flags (int,int) ; 
 int /*<<< orphan*/  emit_andimm (int,int,int) ; 
 int /*<<< orphan*/  emit_orreq_imm (int,int,int) ; 

void emit_dt(int t, int sr)
{
  emit_andimm(sr,~1,sr);
  emit_addimm_and_set_flags(-1,t);
  emit_orreq_imm(sr,1,sr);
}