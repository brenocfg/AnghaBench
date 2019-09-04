#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  top; } ;
typedef  TYPE_1__ lua_State ;
typedef  int /*<<< orphan*/  l_noret ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
 int /*<<< orphan*/  api_incr_top (TYPE_1__*) ; 
 int /*<<< orphan*/  luaD_throw (TYPE_1__*,int) ; 
 int /*<<< orphan*/  luaS_new (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  setsvalue2s (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static l_noret resume_error (lua_State *L, const char *msg, StkId firstArg) {
  L->top = firstArg;  /* remove args from the stack */
  setsvalue2s(L, L->top, luaS_new(L, msg));  /* push error message */
  api_incr_top(L);
  luaD_throw(L, -1);  /* jump back to 'lua_resume' */
}