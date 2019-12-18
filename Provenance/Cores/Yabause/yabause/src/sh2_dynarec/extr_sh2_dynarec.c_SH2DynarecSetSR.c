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
typedef  void* u32 ;
typedef  int /*<<< orphan*/  SH2_struct ;

/* Variables and functions */
 int /*<<< orphan*/ * MSH2 ; 
 size_t SR ; 
 void** master_reg ; 
 void** slave_reg ; 

void SH2DynarecSetSR(SH2_struct *context, u32 value) {
  if(context==MSH2) 
    master_reg[SR]=value;
  else 
    slave_reg[SR]=value;
}