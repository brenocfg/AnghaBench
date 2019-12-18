#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  metatable; } ;
typedef  TYPE_2__ Table ;
struct TYPE_6__ {int /*<<< orphan*/  lnglen; } ;
struct TYPE_8__ {TYPE_1__ u; int /*<<< orphan*/  shrlen; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  int /*<<< orphan*/  StkId ;

/* Variables and functions */
#define  LUA_TLNGSTR 130 
#define  LUA_TSHRSTR 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  TM_LEN ; 
 int /*<<< orphan*/ * fasttm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* hvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  luaG_typeerror (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/  luaH_getn (TYPE_2__*) ; 
 int /*<<< orphan*/  luaT_callTM (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * luaT_gettmbyobj (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setivalue (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* tsvalue (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ttisnil (int /*<<< orphan*/  const*) ; 
 int ttype (int /*<<< orphan*/  const*) ; 

void luaV_objlen (lua_State *L, StkId ra, const TValue *rb) {
  const TValue *tm;
  switch (ttype(rb)) {
    case LUA_TTABLE: {
      Table *h = hvalue(rb);
      tm = fasttm(L, h->metatable, TM_LEN);
      if (tm) break;  /* metamethod? break switch to call it */
      setivalue(ra, luaH_getn(h));  /* else primitive len */
      return;
    }
    case LUA_TSHRSTR: {
      setivalue(ra, tsvalue(rb)->shrlen);
      return;
    }
    case LUA_TLNGSTR: {
      setivalue(ra, tsvalue(rb)->u.lnglen);
      return;
    }
    default: {  /* try metamethod */
      tm = luaT_gettmbyobj(L, rb, TM_LEN);
      if (ttisnil(tm))  /* no metamethod? */
        luaG_typeerror(L, rb, "get length of");
      break;
    }
  }
  luaT_callTM(L, tm, rb, rb, ra, 1);
}