#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_8__ {scalar_t__ aux; } ;
struct TYPE_9__ {TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 int addpatt (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 int /*<<< orphan*/  any (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_2__* getpatt (int /*<<< orphan*/ *,int,int*) ; 
 scalar_t__ isany (TYPE_2__*) ; 
 TYPE_2__* newpatt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  optimizecaptures (TYPE_2__*) ; 

__attribute__((used)) static int concat_l (lua_State *L) {
  /* p1; p2; */
  int l1, l2;
  Instruction *p1 = getpatt(L, 1, &l1);
  Instruction *p2 = getpatt(L, 2, &l2);
  if (isany(p1) && isany(p2))
    any(L, p1->i.aux + p2->i.aux, 0, NULL);
  else {
    Instruction *op = newpatt(L, l1 + l2);
    Instruction *p = op + addpatt(L, op, 1);
    addpatt(L, p, 2);
    optimizecaptures(op);
  }
  return 1;
}