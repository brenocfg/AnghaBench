#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {struct TYPE_7__* hash_next; int /*<<< orphan*/  symbol; } ;
typedef  TYPE_1__ hash_table_entry ;

/* Variables and functions */
 TYPE_1__* add_symbol (TYPE_1__*,char const*) ; 
 int hash_mask ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 
 TYPE_1__* xmalloc (int) ; 

__attribute__((used)) static hash_table_entry *
lookup (hash_table_entry *hash_tab_p, const char *search_symbol)
{
  int hash_value = 0;
  const char *search_symbol_char_p = search_symbol;
  hash_table_entry *p;

  while (*search_symbol_char_p)
    hash_value += *search_symbol_char_p++;
  hash_value &= hash_mask;
  p = &hash_tab_p[hash_value];
  if (! p->symbol)
      return add_symbol (p, search_symbol);
  if (!strcmp (p->symbol, search_symbol))
    return p;
  while (p->hash_next)
    {
      p = p->hash_next;
      if (!strcmp (p->symbol, search_symbol))
	return p;
    }
  p->hash_next = xmalloc (sizeof (hash_table_entry));
  p = p->hash_next;
  return add_symbol (p, search_symbol);
}