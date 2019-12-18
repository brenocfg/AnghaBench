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
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 int /*<<< orphan*/ * getpatt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getfenv (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int lua_objlen (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawgeti (int /*<<< orphan*/ *,int,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_type (int /*<<< orphan*/ *,int) ; 
 char* lua_typename (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  printpatt (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int printpat_l (lua_State *L) {
  Instruction *p = getpatt(L, 1, NULL);
  int n, i;
  lua_getfenv(L, 1);
  n = lua_objlen(L, -1);
  printf("[");
  for (i = 1; i <= n; i++) {
    printf("%d = ", i);
    lua_rawgeti(L, -1, i);
    if (lua_isstring(L, -1))
      printf("%s  ", lua_tostring(L, -1));
    else
      printf("%s  ", lua_typename(L, lua_type(L, -1)));
    lua_pop(L, 1);
  }
  printf("]\n");
  printpatt(p);
  return 0;
}