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
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/ * lua_CFunction ;

/* Variables and functions */
 int ERRFUNC ; 
 int ERRLIB ; 
 int /*<<< orphan*/  ll_addtoclib (int /*<<< orphan*/ *,char const*,void*) ; 
 void* ll_checkclib (int /*<<< orphan*/ *,char const*) ; 
 void* ll_load (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/ * ll_sym (int /*<<< orphan*/ *,void*,char const*) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ll_loadfunc (lua_State *L, const char *path, const char *sym) {
  void *reg = ll_checkclib(L, path);  /* check loaded C libraries */
  if (reg == NULL) {  /* must load library? */
    reg = ll_load(L, path, *sym == '*');
    if (reg == NULL) return ERRLIB;  /* unable to load library */
    ll_addtoclib(L, path, reg);
  }
  if (*sym == '*') {  /* loading only library (no function)? */
    lua_pushboolean(L, 1);  /* return 'true' */
    return 0;  /* no errors */
  }
  else {
    lua_CFunction f = ll_sym(L, reg, sym);
    if (f == NULL)
      return ERRFUNC;  /* unable to find function */
    lua_pushcfunction(L, f);  /* else create new function */
    return 0;  /* no errors */
  }
}