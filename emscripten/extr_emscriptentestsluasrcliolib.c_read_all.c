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
typedef  int /*<<< orphan*/  luaL_Buffer ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t LUAL_BUFFERSIZE ; 
 int MAX_SIZE_T ; 
 size_t fread (char*,int,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_addsize (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  luaL_buffinit (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* luaL_prepbuffsize (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  luaL_pushresult (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void read_all (lua_State *L, FILE *f) {
  size_t rlen = LUAL_BUFFERSIZE;  /* how much to read in each cycle */
  luaL_Buffer b;
  luaL_buffinit(L, &b);
  for (;;) {
    char *p = luaL_prepbuffsize(&b, rlen);
    size_t nr = fread(p, sizeof(char), rlen, f);
    luaL_addsize(&b, nr);
    if (nr < rlen) break;  /* eof? */
    else if (rlen <= (MAX_SIZE_T / 4))  /* avoid buffers too large */
      rlen *= 2;  /* double buffer size at each iteration */
  }
  luaL_pushresult(&b);  /* close buffer */
}