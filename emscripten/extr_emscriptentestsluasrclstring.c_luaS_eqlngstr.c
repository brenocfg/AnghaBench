#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t len; scalar_t__ tt; } ;
struct TYPE_7__ {TYPE_1__ tsv; } ;
typedef  TYPE_2__ TString ;

/* Variables and functions */
 scalar_t__ LUA_TLNGSTR ; 
 int /*<<< orphan*/  getstr (TYPE_2__*) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

int luaS_eqlngstr (TString *a, TString *b) {
  size_t len = a->tsv.len;
  lua_assert(a->tsv.tt == LUA_TLNGSTR && b->tsv.tt == LUA_TLNGSTR);
  return (a == b) ||  /* same instance or... */
    ((len == b->tsv.len) &&  /* equal length and ... */
     (memcmp(getstr(a), getstr(b), len) == 0));  /* equal contents */
}