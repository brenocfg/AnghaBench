#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  jointable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * newpatt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Instruction *auxnew (lua_State *L, Instruction **op, int *size,
                                         int extra) {
  *op = newpatt(L, *size + extra);
  jointable(L, 1);
  *size += extra;
  return *op + *size - extra;
}