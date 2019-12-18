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
 int Cclose ; 
 int /*<<< orphan*/  ICloseCapture ; 
 int /*<<< orphan*/  IFullCapture ; 
 int /*<<< orphan*/  IOpenCapture ; 
 int /*<<< orphan*/  addpatt (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int getlabel (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * getpatt (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/ * newpatt (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  optimizecaptures (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setinstcap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int skipchecks (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int capture_aux (lua_State *L, int kind, int labelidx) {
  int l1, n;
  Instruction *p1 = getpatt(L, 1, &l1);
  int lc = skipchecks(p1, 0, &n);
  if (lc == l1) {  /* got whole pattern? */
    /* may use a IFullCapture instruction at its end */
    Instruction *p = newpatt(L, l1 + 1);
    int label = getlabel(L, labelidx);
    p += addpatt(L, p, 1);
    setinstcap(p, IFullCapture, label, kind, n);
  }
  else {  /* must use open-close pair */
    Instruction *op = newpatt(L, 1 + l1 + 1);
    Instruction *p = op;
    setinstcap(p++, IOpenCapture, getlabel(L, labelidx), kind, 0);
    p += addpatt(L, p, 1);
    setinstcap(p, ICloseCapture, 0, Cclose, 0);
    optimizecaptures(op);
  }
  return 1;
}