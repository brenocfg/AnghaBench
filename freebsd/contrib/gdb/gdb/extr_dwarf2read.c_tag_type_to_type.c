#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct type {int dummy; } ;
struct dwarf2_cu {TYPE_1__* objfile; } ;
struct die_info {struct type* type; int /*<<< orphan*/  tag; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dump_die (struct die_info*) ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  read_type_die (struct die_info*,struct dwarf2_cu*) ; 

__attribute__((used)) static struct type *
tag_type_to_type (struct die_info *die, struct dwarf2_cu *cu)
{
  if (die->type)
    {
      return die->type;
    }
  else
    {
      read_type_die (die, cu);
      if (!die->type)
	{
	  dump_die (die);
	  error ("Dwarf Error: Cannot find type of die 0x%x [in module %s]", 
			  die->tag, cu->objfile->name);
	}
      return die->type;
    }
}