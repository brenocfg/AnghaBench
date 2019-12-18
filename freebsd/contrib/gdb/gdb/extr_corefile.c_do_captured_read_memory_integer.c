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
typedef  int /*<<< orphan*/  CORE_ADDR ;

/* Variables and functions */
 int /*<<< orphan*/  read_memory_integer (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
do_captured_read_memory_integer (void *data)
{
  struct captured_read_memory_integer_arguments *args = (struct captured_read_memory_integer_arguments*) data;
  CORE_ADDR memaddr = args->memaddr;
  int len = args->len;

  args->result = read_memory_integer (memaddr, len);

  return 1;
}