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
struct TYPE_2__ {char* name; } ;
struct symbol {TYPE_1__ ginfo; } ;
struct pending {scalar_t__ nsyms; struct symbol** symbol; struct pending* next; } ;

/* Variables and functions */
 scalar_t__ PENDINGSIZE ; 
 scalar_t__ SYMBOL_LANGUAGE (struct symbol*) ; 
 int /*<<< orphan*/  cp_scan_for_anonymous_namespaces (struct symbol*) ; 
 struct pending* free_pendings ; 
 scalar_t__ language_cplus ; 
 scalar_t__ xmalloc (int) ; 

void
add_symbol_to_list (struct symbol *symbol, struct pending **listhead)
{
  struct pending *link;

  /* If this is an alias for another symbol, don't add it.  */
  if (symbol->ginfo.name && symbol->ginfo.name[0] == '#')
    return;

  /* We keep PENDINGSIZE symbols in each link of the list. If we
     don't have a link with room in it, add a new link.  */
  if (*listhead == NULL || (*listhead)->nsyms == PENDINGSIZE)
    {
      if (free_pendings)
	{
	  link = free_pendings;
	  free_pendings = link->next;
	}
      else
	{
	  link = (struct pending *) xmalloc (sizeof (struct pending));
	}

      link->next = *listhead;
      *listhead = link;
      link->nsyms = 0;
    }

  (*listhead)->symbol[(*listhead)->nsyms++] = symbol;

  /* Check to see if we might need to look for a mention of anonymous
     namespaces.  */
  
  if (SYMBOL_LANGUAGE (symbol) == language_cplus)
    cp_scan_for_anonymous_namespaces (symbol);
}