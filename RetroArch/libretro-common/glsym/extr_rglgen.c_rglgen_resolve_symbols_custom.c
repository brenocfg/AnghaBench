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
struct rglgen_sym_map {int /*<<< orphan*/  ptr; scalar_t__ sym; } ;
typedef  int /*<<< orphan*/  (* rglgen_proc_address_t ) (scalar_t__) ;
typedef  int /*<<< orphan*/  rglgen_func_t ;
typedef  int /*<<< orphan*/  func ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

void rglgen_resolve_symbols_custom(rglgen_proc_address_t proc,
      const struct rglgen_sym_map *map)
{
   for (; map->sym; map++)
   {
      rglgen_func_t func = proc(map->sym);
      memcpy(map->ptr, &func, sizeof(func));
   }
}