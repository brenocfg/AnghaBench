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
struct TYPE_2__ {unsigned int ident; } ;
struct pragma_entry {int is_deferred; int allow_expansion; TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  cpp_reader ;

/* Variables and functions */
 struct pragma_entry* register_pragma_1 (int /*<<< orphan*/ *,char const*,char const*,int) ; 

void
cpp_register_deferred_pragma (cpp_reader *pfile, const char *space,
			      const char *name, unsigned int ident,
			      bool allow_expansion, bool allow_name_expansion)
{
  struct pragma_entry *entry;

  entry = register_pragma_1 (pfile, space, name, allow_name_expansion);
  if (entry)
    {
      entry->is_deferred = true;
      entry->allow_expansion = allow_expansion;
      entry->u.ident = ident;
    }
}