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
 int /*<<< orphan*/  cpp_token_one ; 
 int /*<<< orphan*/  cpp_token_zero ; 
 int /*<<< orphan*/  define_obj_macro (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  include_guard ; 
 int /*<<< orphan*/  macros ; 
 char* map_get (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool guarded(char *path) {
    char *guard = map_get(include_guard, path);
    bool r = (guard && map_get(macros, guard));
    define_obj_macro("__8cc_include_guard", r ? cpp_token_one : cpp_token_zero);
    return r;
}