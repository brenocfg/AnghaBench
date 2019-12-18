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
typedef  scalar_t__ uint64_t ;
struct module {scalar_t__ core_size; scalar_t__ module_core; } ;

/* Variables and functions */

__attribute__((used)) static inline int
in_core (const struct module *mod, uint64_t addr)
{
	return addr - (uint64_t) mod->module_core < mod->core_size;
}