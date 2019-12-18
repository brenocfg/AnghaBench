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
struct partial_symtab {int n_global_syms; int n_static_syms; int globals_offset; int statics_offset; TYPE_3__* objfile; } ;
struct partial_symbol {int dummy; } ;
typedef  scalar_t__ domain_enum ;
struct TYPE_5__ {struct partial_symbol** list; } ;
struct TYPE_4__ {struct partial_symbol** list; } ;
struct TYPE_6__ {TYPE_2__ static_psymbols; TYPE_1__ global_psymbols; } ;

/* Variables and functions */
 char* DEPRECATED_SYMBOL_NAME (struct partial_symbol*) ; 
 scalar_t__ SYMBOL_DOMAIN (struct partial_symbol*) ; 
 scalar_t__ is_name_suffix (char*) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int strlen (char const*) ; 
 int strncmp (char const*,char*,int) ; 
 scalar_t__ wild_match (char const*,int,char*) ; 

__attribute__((used)) static struct partial_symbol *
ada_lookup_partial_symbol (struct partial_symtab *pst, const char *name,
			   int global, domain_enum domain, int wild)
{
  struct partial_symbol **start;
  int name_len = strlen (name);
  int length = (global ? pst->n_global_syms : pst->n_static_syms);
  int i;

  if (length == 0)
    {
      return (NULL);
    }

  start = (global ?
	   pst->objfile->global_psymbols.list + pst->globals_offset :
	   pst->objfile->static_psymbols.list + pst->statics_offset);

  if (wild)
    {
      for (i = 0; i < length; i += 1)
	{
	  struct partial_symbol *psym = start[i];

	  if (SYMBOL_DOMAIN (psym) == domain &&
	      wild_match (name, name_len, DEPRECATED_SYMBOL_NAME (psym)))
	    return psym;
	}
      return NULL;
    }
  else
    {
      if (global)
	{
	  int U;
	  i = 0;
	  U = length - 1;
	  while (U - i > 4)
	    {
	      int M = (U + i) >> 1;
	      struct partial_symbol *psym = start[M];
	      if (DEPRECATED_SYMBOL_NAME (psym)[0] < name[0])
		i = M + 1;
	      else if (DEPRECATED_SYMBOL_NAME (psym)[0] > name[0])
		U = M - 1;
	      else if (strcmp (DEPRECATED_SYMBOL_NAME (psym), name) < 0)
		i = M + 1;
	      else
		U = M;
	    }
	}
      else
	i = 0;

      while (i < length)
	{
	  struct partial_symbol *psym = start[i];

	  if (SYMBOL_DOMAIN (psym) == domain)
	    {
	      int cmp = strncmp (name, DEPRECATED_SYMBOL_NAME (psym), name_len);

	      if (cmp < 0)
		{
		  if (global)
		    break;
		}
	      else if (cmp == 0
		       && is_name_suffix (DEPRECATED_SYMBOL_NAME (psym) + name_len))
		return psym;
	    }
	  i += 1;
	}

      if (global)
	{
	  int U;
	  i = 0;
	  U = length - 1;
	  while (U - i > 4)
	    {
	      int M = (U + i) >> 1;
	      struct partial_symbol *psym = start[M];
	      if (DEPRECATED_SYMBOL_NAME (psym)[0] < '_')
		i = M + 1;
	      else if (DEPRECATED_SYMBOL_NAME (psym)[0] > '_')
		U = M - 1;
	      else if (strcmp (DEPRECATED_SYMBOL_NAME (psym), "_ada_") < 0)
		i = M + 1;
	      else
		U = M;
	    }
	}
      else
	i = 0;

      while (i < length)
	{
	  struct partial_symbol *psym = start[i];

	  if (SYMBOL_DOMAIN (psym) == domain)
	    {
	      int cmp;

	      cmp = (int) '_' - (int) DEPRECATED_SYMBOL_NAME (psym)[0];
	      if (cmp == 0)
		{
		  cmp = strncmp ("_ada_", DEPRECATED_SYMBOL_NAME (psym), 5);
		  if (cmp == 0)
		    cmp = strncmp (name, DEPRECATED_SYMBOL_NAME (psym) + 5, name_len);
		}

	      if (cmp < 0)
		{
		  if (global)
		    break;
		}
	      else if (cmp == 0
		       && is_name_suffix (DEPRECATED_SYMBOL_NAME (psym) + name_len + 5))
		return psym;
	    }
	  i += 1;
	}

    }
  return NULL;
}