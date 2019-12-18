#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Vector ;
struct TYPE_4__ {int /*<<< orphan*/  sval; } ;
typedef  TYPE_1__ Token ;
typedef  int /*<<< orphan*/  Map ;
typedef  int /*<<< orphan*/  Macro ;

/* Variables and functions */
 int /*<<< orphan*/  hashhash_check (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  macros ; 
 int /*<<< orphan*/ * make_func_macro (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * make_map () ; 
 int /*<<< orphan*/  map_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  map_put (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * read_funclike_macro_body (int /*<<< orphan*/ *) ; 
 int read_funclike_macro_params (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_funclike_macro(Token *name) {
    Map *param = make_map();
    bool is_varg = read_funclike_macro_params(name, param);
    Vector *body = read_funclike_macro_body(param);
    hashhash_check(body);
    Macro *macro = make_func_macro(body, map_len(param), is_varg);
    map_put(macros, name->sval, macro);
}