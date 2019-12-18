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
struct ui_file {int dummy; } ;
typedef  int /*<<< orphan*/  ULONGEST ;
typedef  int CORE_ADDR ;

/* Variables and functions */
 int HOST_CHAR_BIT ; 
 int TARGET_ADDR_BIT ; 
 int /*<<< orphan*/  print_longest (struct ui_file*,char,int,int /*<<< orphan*/ ) ; 

void
print_address_numeric (CORE_ADDR addr, int use_local, struct ui_file *stream)
{
  /* Truncate address to the size of a target address, avoiding shifts
     larger or equal than the width of a CORE_ADDR.  The local
     variable ADDR_BIT stops the compiler reporting a shift overflow
     when it won't occur. */
  /* NOTE: This assumes that the significant address information is
     kept in the least significant bits of ADDR - the upper bits were
     either zero or sign extended.  Should ADDRESS_TO_POINTER() or
     some ADDRESS_TO_PRINTABLE() be used to do the conversion?  */

  int addr_bit = TARGET_ADDR_BIT;

  if (addr_bit < (sizeof (CORE_ADDR) * HOST_CHAR_BIT))
    addr &= ((CORE_ADDR) 1 << addr_bit) - 1;
  print_longest (stream, 'x', use_local, (ULONGEST) addr);
}