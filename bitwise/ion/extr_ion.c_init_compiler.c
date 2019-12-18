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

/* Variables and functions */
 int /*<<< orphan*/  decl_note_names ; 
 int /*<<< orphan*/  declare_note_name ; 
 int /*<<< orphan*/  init_builtin_types () ; 
 int /*<<< orphan*/  init_keywords () ; 
 int /*<<< orphan*/  init_package_search_paths () ; 
 int /*<<< orphan*/  init_target () ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ; 

void init_compiler(void) {
    init_target();
    init_package_search_paths();
    init_keywords();
    init_builtin_types();
    map_put(&decl_note_names, declare_note_name, (void *)1);
}