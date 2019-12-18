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
struct rmsgpack_dom_value {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int libretrodb_lua_to_rmsgpack_value (int /*<<< orphan*/ *,int,struct rmsgpack_dom_value*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_isnil (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_istable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static int value_provider(void * ctx, struct rmsgpack_dom_value *out)
{
   int rv        = 0;
   lua_State * L = ctx;

   lua_getglobal(L, "get_value");

   if (lua_pcall(L, 0, 1, 0) != 0)
   {
      printf(
            "error running function `get_value': %s\n",
            lua_tostring(L, -1)
            );
   }

   if (lua_isnil(L, -1))
      rv = 1;
   else if (lua_istable(L, -1))
      rv = libretrodb_lua_to_rmsgpack_value(L, -1, out);
   else
      printf("function `get_value' must return a table or nil\n");
   lua_pop(L, 1);
   return rv;
}