#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  r ;
struct TYPE_9__ {int /*<<< orphan*/ * top; } ;
typedef  TYPE_2__ lua_State ;
typedef  scalar_t__ lua_Number ;
struct TYPE_10__ {TYPE_1__* ls; } ;
struct TYPE_8__ {TYPE_2__* L; } ;
typedef  int /*<<< orphan*/  TValue ;
typedef  TYPE_3__ FuncState ;

/* Variables and functions */
 int addk (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaS_newlstr (TYPE_2__*,char*,int) ; 
 scalar_t__ luai_numisnan (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setnvalue (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  setsvalue (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int luaK_numberK (FuncState *fs, lua_Number r) {
  int n;
  lua_State *L = fs->ls->L;
  TValue o;
  setnvalue(&o, r);
  if (r == 0 || luai_numisnan(NULL, r)) {  /* handle -0 and NaN */
    /* use raw representation as key to avoid numeric problems */
    setsvalue(L, L->top++, luaS_newlstr(L, (char *)&r, sizeof(r)));
    n = addk(fs, L->top - 1, &o);
    L->top--;
  }
  else
    n = addk(fs, &o, &o);  /* regular case */
  return n;
}