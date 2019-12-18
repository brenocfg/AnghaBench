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
typedef  int /*<<< orphan*/  Token ;

/* Variables and functions */
 int /*<<< orphan*/  macros ; 
 int /*<<< orphan*/  make_obj_macro (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_vector1 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void define_obj_macro(char *name, Token *value) {
    map_put(macros, name, make_obj_macro(make_vector1(value)));
}