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
 int /*<<< orphan*/  expect_prompt (int) ; 
 int /*<<< orphan*/  get_reg_name (int) ; 
 int /*<<< orphan*/  printf_stdebug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_register (int) ; 
 int /*<<< orphan*/  st2000_store_registers () ; 

__attribute__((used)) static void
st2000_store_register (int regno)
{
  if (regno == -1)
    st2000_store_registers ();
  else
    {
      printf_stdebug ("PR %s %x\r", get_reg_name (regno),
		      read_register (regno));

      expect_prompt (1);
    }
}