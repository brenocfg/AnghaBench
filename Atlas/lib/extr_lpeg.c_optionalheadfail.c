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
 int /*<<< orphan*/  addpatt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  check2test (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * newpatt (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void optionalheadfail (lua_State *L, int l1, int n) {
  Instruction *op = newpatt(L, n * l1);
  Instruction *p = op;
  int i;
  for (i = 0; i < n; i++) {
    p += addpatt(L, p, 1);
    check2test(p - l1, (n - i)*l1);
  }
}