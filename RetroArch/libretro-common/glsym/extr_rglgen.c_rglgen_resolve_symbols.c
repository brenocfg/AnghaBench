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
typedef  int /*<<< orphan*/  rglgen_proc_address_t ;

/* Variables and functions */
 int /*<<< orphan*/  rglgen_resolve_symbols_custom (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rglgen_symbol_map ; 

void rglgen_resolve_symbols(rglgen_proc_address_t proc)
{
   if (!proc)
      return;

   rglgen_resolve_symbols_custom(proc, rglgen_symbol_map);
}