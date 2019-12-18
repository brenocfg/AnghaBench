#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  syms_map; } ;
typedef  int /*<<< orphan*/  Sym ;
typedef  TYPE_1__ Package ;

/* Variables and functions */
 int /*<<< orphan*/ * map_get (int /*<<< orphan*/ *,char const*) ; 

Sym *get_package_sym(Package *package, const char *name) {
    return map_get(&package->syms_map, name);
}