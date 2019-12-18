#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ symbol ;
struct TYPE_6__ {int /*<<< orphan*/  mangled; } ;
typedef  TYPE_2__ demangled ;

/* Variables and functions */
 int DMGL_ANSI ; 
 int DMGL_PARAMS ; 
 char* cplus_demangle (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* demangled_hash_lookup (char const*,int) ; 
 TYPE_1__* symbol_pop () ; 

__attribute__((used)) static void
demangle_new_symbols (void)
{
  symbol *sym;

  while ((sym = symbol_pop ()) != NULL)
    {
      demangled *dem;
      const char *p = cplus_demangle (sym->key, DMGL_PARAMS | DMGL_ANSI);

      if (! p)
	continue;

      dem = demangled_hash_lookup (p, true);
      dem->mangled = sym->key;
    }
}