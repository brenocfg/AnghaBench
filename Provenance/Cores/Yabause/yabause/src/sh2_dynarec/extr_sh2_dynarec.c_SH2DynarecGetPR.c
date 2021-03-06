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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  SH2_struct ;

/* Variables and functions */
 int /*<<< orphan*/ * MSH2 ; 
 size_t PR ; 
 int /*<<< orphan*/ * master_reg ; 
 int /*<<< orphan*/ * slave_reg ; 

u32 SH2DynarecGetPR(SH2_struct *context)
{
  if(context==MSH2) 
    return master_reg[PR];
  else
    return slave_reg[PR];
}