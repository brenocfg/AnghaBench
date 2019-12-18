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

/* Variables and functions */
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char const*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static int call_init(lua_State * L, int argc, const char ** argv)
{
   int rv = -1;
   int i;

   lua_getglobal(L, "init");
   for (i = 0; i < argc; i++)
      lua_pushstring(L, argv[i]);

   if (lua_pcall(L, argc, 0, 0) != 0)
   {
      printf(
            "error running function `init': %s\n",
            lua_tostring(L, -1)
            );
   }

   return rv;
}