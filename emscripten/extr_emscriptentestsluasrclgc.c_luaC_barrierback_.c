#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/ * grayagain; } ;
typedef  TYPE_1__ global_State ;
struct TYPE_8__ {scalar_t__ tt; } ;
struct TYPE_7__ {int /*<<< orphan*/ * gclist; } ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_1__* G (int /*<<< orphan*/ *) ; 
 scalar_t__ LUA_TTABLE ; 
 int /*<<< orphan*/  black2gray (int /*<<< orphan*/ *) ; 
 TYPE_4__* gch (int /*<<< orphan*/ *) ; 
 TYPE_3__* gco2t (int /*<<< orphan*/ *) ; 
 scalar_t__ isblack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  isdead (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_assert (int) ; 

void luaC_barrierback_ (lua_State *L, GCObject *o) {
  global_State *g = G(L);
  lua_assert(isblack(o) && !isdead(g, o) && gch(o)->tt == LUA_TTABLE);
  black2gray(o);  /* make object gray (again) */
  gco2t(o)->gclist = g->grayagain;
  g->grayagain = o;
}