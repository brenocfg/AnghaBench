#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__ const* null_entry; TYPE_1__** name_hash_table; } ;
struct TYPE_7__ {char* name; struct TYPE_7__* next_name; } ;
typedef  TYPE_1__ CGEN_KEYWORD_ENTRY ;
typedef  TYPE_2__ CGEN_KEYWORD ;

/* Variables and functions */
 scalar_t__ ISALPHA (char const) ; 
 scalar_t__ TOLOWER (char const) ; 
 int /*<<< orphan*/  build_keyword_hash_tables (TYPE_2__*) ; 
 size_t hash_keyword_name (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 

const CGEN_KEYWORD_ENTRY *
cgen_keyword_lookup_name (CGEN_KEYWORD *kt, const char *name)
{
  const CGEN_KEYWORD_ENTRY *ke;
  const char *p,*n;

  if (kt->name_hash_table == NULL)
    build_keyword_hash_tables (kt);

  ke = kt->name_hash_table[hash_keyword_name (kt, name, 0)];

  /* We do case insensitive comparisons.
     If that ever becomes a problem, add an attribute that denotes
     "do case sensitive comparisons".  */

  while (ke != NULL)
    {
      n = name;
      p = ke->name;

      while (*p
	     && (*p == *n
		 || (ISALPHA (*p) && (TOLOWER (*p) == TOLOWER (*n)))))
	++n, ++p;

      if (!*p && !*n)
	return ke;

      ke = ke->next_name;
    }

  if (kt->null_entry)
    return kt->null_entry;
  return NULL;
}