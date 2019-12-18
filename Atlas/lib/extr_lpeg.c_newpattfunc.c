#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int offset; int /*<<< orphan*/  code; } ;
struct TYPE_5__ {int /*<<< orphan*/  buff; int /*<<< orphan*/  f; TYPE_1__ i; } ;
typedef  int /*<<< orphan*/  PattFunc ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  IFunc ; 
 int instsize (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,size_t) ; 
 TYPE_2__* newpatt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void newpattfunc (lua_State *L, PattFunc f, const void *ud, size_t l) {
  int n = instsize(l) + 1;
  Instruction *p = newpatt(L, n);
  p[0].i.code = IFunc;
  p[0].i.offset = n;
  p[1].f = f;
  memcpy(p[2].buff, ud, l);
}