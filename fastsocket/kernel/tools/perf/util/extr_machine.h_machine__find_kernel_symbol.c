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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  symbol_filter_t ;
struct symbol {int dummy; } ;
struct map {int dummy; } ;
struct machine {int /*<<< orphan*/  kmaps; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 struct symbol* map_groups__find_symbol (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct map**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline
struct symbol *machine__find_kernel_symbol(struct machine *machine,
					   enum map_type type, u64 addr,
					   struct map **mapp,
					   symbol_filter_t filter)
{
	return map_groups__find_symbol(&machine->kmaps, type, addr,
				       mapp, filter);
}