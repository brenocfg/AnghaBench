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
struct minimal_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  ps_err_e ;
typedef  int /*<<< orphan*/  paddr_t ;
typedef  int /*<<< orphan*/  gdb_ps_prochandle_t ;

/* Variables and functions */
 int /*<<< orphan*/  PS_NOSYM ; 
 int /*<<< orphan*/  PS_OK ; 
 int /*<<< orphan*/  SYMBOL_VALUE_ADDRESS (struct minimal_symbol*) ; 
 struct minimal_symbol* lookup_minimal_symbol (char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

ps_err_e
ps_pglobal_lookup (gdb_ps_prochandle_t ph, const char *obj,
		   const char *name, paddr_t *sym_addr)
{
  struct minimal_symbol *ms;

  /* FIXME: kettenis/2000-09-03: What should we do with OBJ?  */
  ms = lookup_minimal_symbol (name, NULL, NULL);
  if (ms == NULL)
    return PS_NOSYM;

  *sym_addr = SYMBOL_VALUE_ADDRESS (ms);
  return PS_OK;
}