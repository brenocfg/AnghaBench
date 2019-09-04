#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ k; } ;
struct ConsControl {scalar_t__ tostore; int /*<<< orphan*/  na; TYPE_2__* t; TYPE_3__ v; } ;
struct TYPE_5__ {int /*<<< orphan*/  info; } ;
struct TYPE_6__ {TYPE_1__ u; } ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 scalar_t__ LUA_MULTRET ; 
 scalar_t__ VVOID ; 
 scalar_t__ hasmultret (scalar_t__) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_setlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  luaK_setmultret (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void lastlistfield (FuncState *fs, struct ConsControl *cc) {
  if (cc->tostore == 0) return;
  if (hasmultret(cc->v.k)) {
    luaK_setmultret(fs, &cc->v);
    luaK_setlist(fs, cc->t->u.info, cc->na, LUA_MULTRET);
    cc->na--;  /* do not count last expression (unknown number of elements) */
  }
  else {
    if (cc->v.k != VVOID)
      luaK_exp2nextreg(fs, &cc->v);
    luaK_setlist(fs, cc->t->u.info, cc->na, cc->tostore);
  }
}