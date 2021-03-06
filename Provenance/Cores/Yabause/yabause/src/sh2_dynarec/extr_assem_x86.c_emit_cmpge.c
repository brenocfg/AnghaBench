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
 int /*<<< orphan*/  emit_addimm (int,int,int) ; 
 int /*<<< orphan*/  emit_cmovl_reg (int,int) ; 
 int /*<<< orphan*/  emit_cmp (int,int) ; 
 int /*<<< orphan*/  emit_orimm (int,int,int) ; 

void emit_cmpge(int s1, int s2, int sr, int temp)
{
  assert(temp>=0);
  emit_orimm(sr,1,sr);
  emit_addimm(sr,-1,temp);
  emit_cmp(s2,s1);
  emit_cmovl_reg(temp,sr);
}