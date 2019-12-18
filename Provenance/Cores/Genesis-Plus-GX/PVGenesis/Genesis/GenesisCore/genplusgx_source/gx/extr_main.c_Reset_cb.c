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
 int /*<<< orphan*/  IO_RESET_HI ; 
 int SYSTEM_MD ; 
 int SYSTEM_SMS ; 
 int /*<<< orphan*/  gen_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * io_reg ; 
 int system_hw ; 

__attribute__((used)) static void Reset_cb(void)
{
  if (system_hw & SYSTEM_MD)
  {
    /* Soft Reset */
    gen_reset(0);
  }
  else if (system_hw == SYSTEM_SMS)
  {
    /* assert RESET input (Master System model 1 only) */
    io_reg[0x0D] &= ~IO_RESET_HI;
  }
}