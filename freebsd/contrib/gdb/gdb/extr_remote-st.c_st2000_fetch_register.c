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
 int /*<<< orphan*/  expect (char*,int) ; 
 int /*<<< orphan*/  expect_prompt (int) ; 
 int /*<<< orphan*/  get_hex_regs (int,int) ; 
 char* get_reg_name (int) ; 
 int /*<<< orphan*/  printf_stdebug (char*,char*) ; 
 int /*<<< orphan*/  st2000_fetch_registers () ; 

__attribute__((used)) static void
st2000_fetch_register (int regno)
{
  if (regno == -1)
    st2000_fetch_registers ();
  else
    {
      char *name = get_reg_name (regno);
      printf_stdebug ("DR %s\r", name);
      expect (name, 1);
      expect (" : ", 1);
      get_hex_regs (1, regno);
      expect_prompt (1);
    }
  return;
}