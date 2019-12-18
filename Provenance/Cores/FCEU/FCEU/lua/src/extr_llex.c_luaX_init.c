#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  reserved; } ;
struct TYPE_6__ {TYPE_1__ tsv; } ;
typedef  TYPE_2__ TString ;

/* Variables and functions */
 int NUM_RESERVED ; 
 scalar_t__ TOKEN_LEN ; 
 int /*<<< orphan*/  cast_byte (int) ; 
 int /*<<< orphan*/  luaS_fix (TYPE_2__*) ; 
 TYPE_2__* luaS_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * luaX_tokens ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 

void luaX_init (lua_State *L) {
  int i;
  for (i=0; i<NUM_RESERVED; i++) {
    TString *ts = luaS_new(L, luaX_tokens[i]);
    luaS_fix(ts);  /* reserved words are never collected */
    lua_assert(strlen(luaX_tokens[i])+1 <= TOKEN_LEN);
    ts->tsv.reserved = cast_byte(i+1);  /* reserved word */
  }
}