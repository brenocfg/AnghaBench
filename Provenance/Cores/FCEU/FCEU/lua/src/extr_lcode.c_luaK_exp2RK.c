#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  info; } ;
struct TYPE_15__ {TYPE_1__ s; int /*<<< orphan*/  nval; } ;
struct TYPE_16__ {int k; TYPE_2__ u; } ;
typedef  TYPE_3__ expdesc ;
struct TYPE_17__ {int /*<<< orphan*/  nk; } ;
typedef  TYPE_4__ FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  MAXINDEXRK ; 
 int RKASK (int /*<<< orphan*/ ) ; 
#define  VFALSE 132 
#define  VK 131 
#define  VKNUM 130 
#define  VNIL 129 
#define  VTRUE 128 
 int /*<<< orphan*/  boolK (TYPE_4__*,int) ; 
 int luaK_exp2anyreg (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_exp2val (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  luaK_numberK (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilK (TYPE_4__*) ; 

int luaK_exp2RK (FuncState *fs, expdesc *e) {
  luaK_exp2val(fs, e);
  switch (e->k) {
    case VKNUM:
    case VTRUE:
    case VFALSE:
    case VNIL: {
      if (fs->nk <= MAXINDEXRK) {  /* constant fit in RK operand? */
        e->u.s.info = (e->k == VNIL)  ? nilK(fs) :
                      (e->k == VKNUM) ? luaK_numberK(fs, e->u.nval) :
                                        boolK(fs, (e->k == VTRUE));
        e->k = VK;
        return RKASK(e->u.s.info);
      }
      else break;
    }
    case VK: {
      if (e->u.s.info <= MAXINDEXRK)  /* constant fit in argC? */
        return RKASK(e->u.s.info);
      else break;
    }
    default: break;
  }
  /* not a constant in the right range: put it in a register */
  return luaK_exp2anyreg(fs, e);
}