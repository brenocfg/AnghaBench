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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int TARGET_BUF_SIZE ; 
 int monitor_expect_prompt (char*,int) ; 
 int /*<<< orphan*/  monitor_printf (char*) ; 
 int /*<<< orphan*/  parse_register_dump (char*,int) ; 

int
monitor_dump_reg_block (char *block_cmd)
{
  char buf[TARGET_BUF_SIZE];
  int resp_len;
  monitor_printf (block_cmd);
  resp_len = monitor_expect_prompt (buf, sizeof (buf));
  parse_register_dump (buf, resp_len);
  return 1;
}