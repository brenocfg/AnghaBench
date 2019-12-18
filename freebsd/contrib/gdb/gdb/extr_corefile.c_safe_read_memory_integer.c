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
struct captured_read_memory_integer_arguments {int len; int /*<<< orphan*/  result; int /*<<< orphan*/  memaddr; } ;
typedef  int /*<<< orphan*/  LONGEST ;
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int catch_errors (int /*<<< orphan*/ ,struct captured_read_memory_integer_arguments*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_captured_read_memory_integer ; 

int
safe_read_memory_integer (CORE_ADDR memaddr, int len, LONGEST *return_value)
{
  int status;
  struct captured_read_memory_integer_arguments args;
  args.memaddr = memaddr;
  args.len = len;

  status = catch_errors (do_captured_read_memory_integer, &args,
                        "", RETURN_MASK_ALL);
  if (status)
    *return_value = args.result;

  return status;
}