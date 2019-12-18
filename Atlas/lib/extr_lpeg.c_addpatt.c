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
struct TYPE_8__ {scalar_t__ offset; } ;
struct TYPE_9__ {TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  copypatt (TYPE_2__*,TYPE_2__*,int) ; 
 scalar_t__ isfenvoff (TYPE_2__*) ; 
 int jointable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int pattsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sizei (TYPE_2__*) ; 

__attribute__((used)) static int addpatt (lua_State *L, Instruction *p, int p1idx) {
  Instruction *p1 = (Instruction *)lua_touserdata(L, p1idx);
  int sz = pattsize(L, p1idx);
  int corr = jointable(L, p1idx);
  copypatt(p, p1, sz + 1);
  if (corr != 0) {
    Instruction *px;
    for (px = p; px < p + sz; px += sizei(px)) {
      if (isfenvoff(px) && px->i.offset != 0)
        px->i.offset += corr;
    }
  }
  return sz;
}