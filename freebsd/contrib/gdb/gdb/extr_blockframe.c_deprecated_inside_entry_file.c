#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ deprecated_entry_file_lowpc; scalar_t__ deprecated_entry_file_highpc; } ;
struct TYPE_4__ {TYPE_1__ ei; } ;
typedef  scalar_t__ CORE_ADDR ;

/* Variables and functions */
 scalar_t__ AT_ENTRY_POINT ; 
 scalar_t__ AT_SYMBOL ; 
 scalar_t__ CALL_DUMMY_LOCATION ; 
 scalar_t__ DEPRECATED_PC_IN_CALL_DUMMY (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* symfile_objfile ; 

int
deprecated_inside_entry_file (CORE_ADDR addr)
{
  if (addr == 0)
    return 1;
  if (symfile_objfile == 0)
    return 0;
  if (CALL_DUMMY_LOCATION == AT_ENTRY_POINT
      || CALL_DUMMY_LOCATION == AT_SYMBOL)
    {
      /* Do not stop backtracing if the pc is in the call dummy
         at the entry point.  */
      /* FIXME: Won't always work with zeros for the last two arguments */
      if (DEPRECATED_PC_IN_CALL_DUMMY (addr, 0, 0))
	return 0;
    }
  return (addr >= symfile_objfile->ei.deprecated_entry_file_lowpc &&
	  addr < symfile_objfile->ei.deprecated_entry_file_highpc);
}