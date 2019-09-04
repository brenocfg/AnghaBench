#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int info; } ;
struct TYPE_14__ {scalar_t__ k; TYPE_1__ u; } ;
typedef  TYPE_2__ expdesc ;
struct TYPE_15__ {scalar_t__ nactvar; } ;
typedef  TYPE_3__ FuncState ;

/* Variables and functions */
 scalar_t__ VNONRELOC ; 
 int /*<<< orphan*/  exp2reg (TYPE_3__*,TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  hasjumps (TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_dischargevars (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_exp2nextreg (TYPE_3__*,TYPE_2__*) ; 

int luaK_exp2anyreg (FuncState *fs, expdesc *e) {
  luaK_dischargevars(fs, e);
  if (e->k == VNONRELOC) {
    if (!hasjumps(e)) return e->u.info;  /* exp is already in a register */
    if (e->u.info >= fs->nactvar) {  /* reg. is not a local? */
      exp2reg(fs, e, e->u.info);  /* put value on it */
      return e->u.info;
    }
  }
  luaK_exp2nextreg(fs, e);  /* default */
  return e->u.info;
}