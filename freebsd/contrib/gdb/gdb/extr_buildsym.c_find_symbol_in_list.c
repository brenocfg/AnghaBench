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
struct symbol {int dummy; } ;
struct pending {int nsyms; struct pending* next; struct symbol** symbol; } ;

/* Variables and functions */
 char* DEPRECATED_SYMBOL_NAME (struct symbol*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 

struct symbol *
find_symbol_in_list (struct pending *list, char *name, int length)
{
  int j;
  char *pp;

  while (list != NULL)
    {
      for (j = list->nsyms; --j >= 0;)
	{
	  pp = DEPRECATED_SYMBOL_NAME (list->symbol[j]);
	  if (*pp == *name && strncmp (pp, name, length) == 0 &&
	      pp[length] == '\0')
	    {
	      return (list->symbol[j]);
	    }
	}
      list = list->next;
    }
  return (NULL);
}