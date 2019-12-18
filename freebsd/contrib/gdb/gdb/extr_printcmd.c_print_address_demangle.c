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
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ addressprint ; 
 int /*<<< orphan*/  fprintf_filtered (struct ui_file*,char*) ; 
 int /*<<< orphan*/  print_address_numeric (scalar_t__,int,struct ui_file*) ; 
 int /*<<< orphan*/  print_address_symbolic (scalar_t__,struct ui_file*,int,char*) ; 

void
print_address_demangle (CORE_ADDR addr, struct ui_file *stream, int do_demangle)
{
  if (addr == 0)
    {
      fprintf_filtered (stream, "0");
    }
  else if (addressprint)
    {
      print_address_numeric (addr, 1, stream);
      print_address_symbolic (addr, stream, do_demangle, " ");
    }
  else
    {
      print_address_symbolic (addr, stream, do_demangle, "");
    }
}