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
struct symbol {int dummy; } ;
struct dso {int /*<<< orphan*/ * symbols; } ;
typedef  enum map_type { ____Placeholder_map_type } map_type ;

/* Variables and functions */
 struct symbol* symbols__find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct symbol *dso__find_symbol(struct dso *dso,
				enum map_type type, u64 addr)
{
	return symbols__find(&dso->symbols[type], addr);
}