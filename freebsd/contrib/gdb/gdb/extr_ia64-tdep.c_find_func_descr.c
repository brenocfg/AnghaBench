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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ FIND_GLOBAL_POINTER (scalar_t__) ; 
 int /*<<< orphan*/  IA64_GR1_REGNUM ; 
 scalar_t__ find_extant_func_descr (scalar_t__) ; 
 scalar_t__ read_register (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_unsigned_integer (char*,int,scalar_t__) ; 
 int /*<<< orphan*/  write_memory (scalar_t__,char*,int) ; 

__attribute__((used)) static CORE_ADDR
find_func_descr (CORE_ADDR faddr, CORE_ADDR *fdaptr)
{
  CORE_ADDR fdesc;

  fdesc = find_extant_func_descr (faddr);

  if (fdesc == 0)
    {
      CORE_ADDR global_pointer;
      char buf[16];

      fdesc = *fdaptr;
      *fdaptr += 16;

      global_pointer = FIND_GLOBAL_POINTER (faddr);

      if (global_pointer == 0)
	global_pointer = read_register (IA64_GR1_REGNUM);

      store_unsigned_integer (buf, 8, faddr);
      store_unsigned_integer (buf + 8, 8, global_pointer);

      write_memory (fdesc, buf, 16);
    }

  return fdesc; 
}