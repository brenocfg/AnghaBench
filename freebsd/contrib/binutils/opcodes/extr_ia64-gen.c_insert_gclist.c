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
struct completer_entry {TYPE_1__* name; struct completer_entry* alternative; struct completer_entry* addl_entries; } ;
struct TYPE_2__ {scalar_t__ num; } ;

/* Variables and functions */
 scalar_t__ completer_entries_eq (struct completer_entry*,struct completer_entry*) ; 
 struct completer_entry** glist ; 
 int glistlen ; 
 int glisttotlen ; 
 scalar_t__ xrealloc (struct completer_entry**,int) ; 

__attribute__((used)) static struct completer_entry *
insert_gclist (struct completer_entry *ent)
{
  if (ent != NULL)
    {
      int i;
      int x;
      int start = 0, end;

      ent->addl_entries = insert_gclist (ent->addl_entries);
      ent->alternative = insert_gclist (ent->alternative);

      i = glistlen / 2;
      end = glistlen;

      if (glisttotlen == glistlen)
	{
	  glisttotlen += 20;
	  glist = (struct completer_entry **)
	    xrealloc (glist, sizeof (struct completer_entry *) * glisttotlen);
	}

      if (glistlen == 0)
	{
	  glist[0] = ent;
	  glistlen = 1;
	  return ent;
	}

      if (ent->name->num < glist[0]->name->num)
	i = 0;
      else if (ent->name->num > glist[end - 1]->name->num)
	i = end;
      else
	{
	  int c;

	  while (1)
	    {
	      i = (start + end) / 2;
	      c = ent->name->num - glist[i]->name->num;

	      if (c < 0)
		end = i - 1;
	      else if (c == 0)
		{
		  while (i > 0 
			 && ent->name->num == glist[i - 1]->name->num)
		    i--;

		  break;
		}
	      else
		start = i + 1;

	      if (start > end)
		break;
	    }

	  if (c == 0)
	    {
	      while (i < glistlen)
		{
		  if (ent->name->num != glist[i]->name->num)
		    break;

		  if (completer_entries_eq (ent, glist[i]))
		    return glist[i];

		  i++;
		}
	    }
	}

      for (; i > 0 && i < glistlen; i--)
	if (ent->name->num >= glist[i - 1]->name->num)
	  break;

      for (; i < glistlen; i++)
	if (ent->name->num < glist[i]->name->num)
	  break;

      for (x = glistlen - 1; x >= i; x--)
	glist[x + 1] = glist[x];

      glist[i] = ent;
      glistlen++;
    }
  return ent;
}