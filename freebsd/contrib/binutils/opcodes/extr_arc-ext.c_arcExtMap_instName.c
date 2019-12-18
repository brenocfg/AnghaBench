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
struct TYPE_4__ {TYPE_1__** instructions; } ;
struct TYPE_3__ {int flags; char const* name; } ;

/* Variables and functions */
 TYPE_2__ arc_extension_map ; 

const char *
arcExtMap_instName(int opcode, int minor, int *flags)
{
    if (opcode == 3)
      {
	/* FIXME: ??? need to also check 0/1/2 in bit0 for (3f) brk/sleep/swi  */
	if (minor < 0x09 || minor == 0x3f)
	  return 0;
	else
	  opcode = 0x1f - 0x10 + minor - 0x09 + 1;
      }
    else
      if (opcode < 0x10)
	return 0;
    else
      opcode -= 0x10;
    if (!arc_extension_map.instructions[opcode])
      return 0;
    *flags = arc_extension_map.instructions[opcode]->flags;
    return arc_extension_map.instructions[opcode]->name;
}