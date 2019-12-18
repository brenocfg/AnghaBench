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
struct regstat {scalar_t__ isdoingcp; } ;

/* Variables and functions */
 int CCREG ; 
 int MOREG ; 
 int SR ; 
 int VBR ; 
 int /*<<< orphan*/  alloc_cc (struct regstat*,int) ; 
 int /*<<< orphan*/  alloc_reg (struct regstat*,int,int) ; 
 int /*<<< orphan*/  alloc_reg_temp (struct regstat*,int,int) ; 
 int /*<<< orphan*/  dirty_reg (struct regstat*,int) ; 
 int* minimum_free_regs ; 
 int* opcode ; 

void system_alloc(struct regstat *current,int i)
{
  alloc_cc(current,i);
  dirty_reg(current,CCREG);
  if(opcode[i]==12) { // TRAPA
    alloc_reg(current,i,15); // Stack reg
    dirty_reg(current,15);
    alloc_reg(current,i,SR); // Status/flags
    alloc_reg(current,i,VBR);
    alloc_reg(current,i,MOREG); // memory_map offset
    alloc_reg_temp(current,i,-1);
    minimum_free_regs[i]=1;
  }
  current->isdoingcp=0;
}