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
typedef  int uint32 ;

/* Variables and functions */
 int /*<<< orphan*/  default_regs_w (int,int) ; 
 int /*<<< orphan*/  mapper_64k_w (int) ; 

__attribute__((used)) static void custom_alt_regs_w(uint32 address, uint32 data)
{
  /* ROM bankswitch */
  if ((address >> 16) > 0x5f)
  {
    mapper_64k_w(data);
    return;
  }

  /* write regs */
  default_regs_w(address, data);
}