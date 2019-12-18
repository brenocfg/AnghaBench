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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {scalar_t__ code; } ;
struct TYPE_7__ {TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;
typedef  int /*<<< orphan*/  CharsetTag ;

/* Variables and functions */
 scalar_t__ IFail ; 
 TYPE_2__* getpatt (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  separateparts (int /*<<< orphan*/ *,TYPE_2__*,int,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tocharset (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int union_l (lua_State *L) {
  int l1, l2;
  int size = 0;
  Instruction *p1 = getpatt(L, 1, &l1);
  Instruction *p2 = getpatt(L, 2, &l2);
  CharsetTag st2;
  if (p1->i.code == IFail)  /* check for identity element */
    lua_pushvalue(L, 2);
  else if (p2->i.code == IFail)
    lua_pushvalue(L, 1);
  else {
    tocharset(p2, &st2);
    separateparts(L, p1, l1, l2, &size, &st2);
  }
  return 1;
}