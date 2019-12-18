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
typedef  int /*<<< orphan*/  SpecialMacroHandler ;

/* Variables and functions */
 int /*<<< orphan*/  macros ; 
 int /*<<< orphan*/  make_special_macro (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void define_special_macro(char *name, SpecialMacroHandler *fn) {
    map_put(macros, name, make_special_macro(fn));
}