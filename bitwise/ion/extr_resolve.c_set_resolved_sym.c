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
typedef  int /*<<< orphan*/  Sym ;

/* Variables and functions */
 int /*<<< orphan*/  is_local_sym (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,void const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resolved_sym_map ; 

void set_resolved_sym(const void *ptr, Sym *sym) {
    if (!is_local_sym(sym)) {
        map_put(&resolved_sym_map, ptr, sym);
    }
}