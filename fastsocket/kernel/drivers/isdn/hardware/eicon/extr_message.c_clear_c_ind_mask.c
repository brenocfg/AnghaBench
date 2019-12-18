#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t word ;
struct TYPE_3__ {scalar_t__* c_ind_mask_table; } ;
typedef  TYPE_1__ PLCI ;

/* Variables and functions */
 size_t C_IND_MASK_DWORDS ; 

__attribute__((used)) static void clear_c_ind_mask (PLCI   *plci)
{
  word i;

  for (i = 0; i < C_IND_MASK_DWORDS; i++)
    plci->c_ind_mask_table[i] = 0;
}