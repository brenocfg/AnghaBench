#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct ia64_opcode {int dummy; } ;
typedef  int ia64_insn ;
typedef  enum ia64_insn_type { ____Placeholder_ia64_insn_type } ia64_insn_type ;
struct TYPE_6__ {int name_index; int subentries; int alternative; int /*<<< orphan*/  dependencies; } ;
struct TYPE_5__ {unsigned int completer_index; int insn_index; } ;
struct TYPE_4__ {int completers; int opcode; size_t name_index; int mask; } ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int apply_completer (int,int) ; 
 TYPE_3__* completer_table ; 
 TYPE_2__* ia64_dis_names ; 
 char** ia64_strings ; 
 int locate_opcode_ent (int,int) ; 
 TYPE_1__* main_table ; 
 struct ia64_opcode* make_ia64_opcode (int,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

struct ia64_opcode *
ia64_dis_opcode (ia64_insn insn, enum ia64_insn_type type)
{
  int disent = locate_opcode_ent (insn, type);

  if (disent < 0)
    {
      return NULL;
    }
  else
    {
      unsigned int cb = ia64_dis_names[disent].completer_index;
      static char name[128];
      int place = ia64_dis_names[disent].insn_index;
      int ci = main_table[place].completers;
      ia64_insn tinsn = main_table[place].opcode;

      strcpy (name, ia64_strings [main_table[place].name_index]);

      while (cb)
	{
	  if (cb & 1)
	    {
	      int cname = completer_table[ci].name_index;

	      tinsn = apply_completer (tinsn, ci);

	      if (ia64_strings[cname][0] != '\0')
		{
		  strcat (name, ".");
		  strcat (name, ia64_strings[cname]);
		}
	      if (cb != 1)
		{
		  ci = completer_table[ci].subentries;
		}
	    }
	  else
	    {
	      ci = completer_table[ci].alternative;
	    }
	  if (ci < 0)
	    {
	      abort ();
	    }
	  cb = cb >> 1;
	}
      if (tinsn != (insn & main_table[place].mask))
	{
	  abort ();
	}
      return make_ia64_opcode (insn, name, place,
                               completer_table[ci].dependencies);
    }
}