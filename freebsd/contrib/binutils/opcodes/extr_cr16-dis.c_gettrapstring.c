#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int entry; char* name; } ;
typedef  TYPE_1__ trap_entry ;

/* Variables and functions */
 char* ILLEGAL ; 
 int NUMTRAPS ; 
 TYPE_1__ const* cr16_traps ; 

__attribute__((used)) static char *
gettrapstring (unsigned int index)
{
  const trap_entry *trap;

  for (trap = cr16_traps; trap < cr16_traps + NUMTRAPS; trap++)
    if (trap->entry == index)
      return trap->name;

  return ILLEGAL;
}