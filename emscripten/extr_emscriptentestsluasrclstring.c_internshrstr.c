#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_13__ {int /*<<< orphan*/  size; int /*<<< orphan*/ ** hash; } ;
struct TYPE_15__ {TYPE_1__ strt; int /*<<< orphan*/  seed; } ;
typedef  TYPE_3__ global_State ;
struct TYPE_14__ {unsigned int hash; size_t len; } ;
struct TYPE_16__ {TYPE_2__ tsv; } ;
struct TYPE_12__ {int /*<<< orphan*/ * next; } ;
typedef  TYPE_4__ TString ;
typedef  int /*<<< orphan*/  GCObject ;

/* Variables and functions */
 TYPE_3__* G (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  changewhite (int /*<<< orphan*/ *) ; 
 TYPE_10__* gch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  getstr (TYPE_4__*) ; 
 scalar_t__ isdead (TYPE_3__*,int /*<<< orphan*/ *) ; 
 size_t lmod (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int luaS_hash (char const*,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 TYPE_4__* newshrstr (int /*<<< orphan*/ *,char const*,size_t,unsigned int) ; 
 TYPE_4__* rawgco2ts (int /*<<< orphan*/ *) ; 

__attribute__((used)) static TString *internshrstr (lua_State *L, const char *str, size_t l) {
  GCObject *o;
  global_State *g = G(L);
  unsigned int h = luaS_hash(str, l, g->seed);
  for (o = g->strt.hash[lmod(h, g->strt.size)];
       o != NULL;
       o = gch(o)->next) {
    TString *ts = rawgco2ts(o);
    if (h == ts->tsv.hash &&
        l == ts->tsv.len &&
        (memcmp(str, getstr(ts), l * sizeof(char)) == 0)) {
      if (isdead(G(L), o))  /* string is dead (but was not collected yet)? */
        changewhite(o);  /* resurrect it */
      return ts;
    }
  }
  return newshrstr(L, str, l, h);  /* not found; create a new string */
}