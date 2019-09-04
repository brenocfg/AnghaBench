#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  varname; } ;
struct TYPE_5__ {int /*<<< orphan*/  nactvar; } ;
typedef  int /*<<< orphan*/  TString ;
typedef  TYPE_1__ FuncState ;

/* Variables and functions */
 int cast_int (int /*<<< orphan*/ ) ; 
 TYPE_3__* getlocvar (TYPE_1__*,int) ; 
 scalar_t__ luaS_eqstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int searchvar (FuncState *fs, TString *n) {
  int i;
  for (i = cast_int(fs->nactvar) - 1; i >= 0; i--) {
    if (luaS_eqstr(n, getlocvar(fs, i)->varname))
      return i;
  }
  return -1;  /* not found */
}