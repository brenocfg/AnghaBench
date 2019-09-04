#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int info; } ;
struct TYPE_8__ {int k; void* t; int /*<<< orphan*/  f; TYPE_1__ u; } ;
typedef  TYPE_2__ expdesc ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 void* NO_JUMP ; 
#define  VJMP 131 
#define  VK 130 
#define  VKNUM 129 
#define  VTRUE 128 
 int /*<<< orphan*/  invertjump (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int jumponcond (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaK_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaK_dischargevars (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  luaK_patchtohere (int /*<<< orphan*/ *,void*) ; 

void luaK_goiftrue (FuncState *fs, expdesc *e) {
  int pc;  /* pc of last jump */
  luaK_dischargevars(fs, e);
  switch (e->k) {
    case VJMP: {
      invertjump(fs, e);
      pc = e->u.info;
      break;
    }
    case VK: case VKNUM: case VTRUE: {
      pc = NO_JUMP;  /* always true; do nothing */
      break;
    }
    default: {
      pc = jumponcond(fs, e, 0);
      break;
    }
  }
  luaK_concat(fs, &e->f, pc);  /* insert last jump in `f' list */
  luaK_patchtohere(fs, e->t);
  e->t = NO_JUMP;
}