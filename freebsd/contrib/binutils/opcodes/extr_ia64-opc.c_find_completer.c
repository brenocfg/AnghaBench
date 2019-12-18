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
struct TYPE_4__ {short subentries; short name_index; short alternative; } ;
struct TYPE_3__ {short completers; } ;

/* Variables and functions */
 TYPE_2__* completer_table ; 
 short find_string_ent (char const*) ; 
 TYPE_1__* main_table ; 

__attribute__((used)) static short
find_completer (short main_ent, short prev_completer, const char *name)
{
  short name_index = find_string_ent (name);

  if (name_index < 0)
    {
      return -1;
    }

  if (prev_completer == -1)
    {
      prev_completer = main_table[main_ent].completers;
    }
  else
    {
      prev_completer = completer_table[prev_completer].subentries;
    }

  while (prev_completer != -1)
    {
      if (completer_table[prev_completer].name_index == name_index)
	{
	  return prev_completer;
	}
      prev_completer = completer_table[prev_completer].alternative;
    }
  return -1;
}