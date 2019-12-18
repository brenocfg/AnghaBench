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
typedef  unsigned int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

u32 rd_rn_rm(unsigned int rd, unsigned int rn, unsigned int rm)
{
  assert(rd<16);
  assert(rn<16);
  assert(rm<16);
  return((rn<<16)|(rd<<12)|rm);
}