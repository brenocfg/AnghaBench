#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_9__ {scalar_t__ code; scalar_t__ offset; } ;
struct TYPE_10__ {TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 scalar_t__ IChoice ; 
 scalar_t__ IOpenCall ; 
 scalar_t__ IPartialCommit ; 
 scalar_t__ IRet ; 
 int /*<<< orphan*/  assert (int) ; 
 int dest (TYPE_2__*,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sizei (TYPE_2__*) ; 
 int /*<<< orphan*/  val2str (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  verify (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,TYPE_2__*,int,int) ; 

__attribute__((used)) static void checkrule (lua_State *L, Instruction *op, int from, int to,
                       int postable, int rule) {
  int i;
  int lastopen = 0;  /* more recent OpenCall seen in the code */
  for (i = from; i < to; i += sizei(op + i)) {
    if (op[i].i.code == IPartialCommit && op[i].i.offset < 0) {  /* loop? */
      int start = dest(op, i);
      assert(op[start - 1].i.code == IChoice && dest(op, start - 1) == i + 1);
      if (start <= lastopen) {  /* loop does contain an open call? */
        if (!verify(L, op, op + start, op + i, postable, rule)) /* check body */
          luaL_error(L, "possible infinite loop in %s", val2str(L, rule));
      }
    }
    else if (op[i].i.code == IOpenCall)
      lastopen = i;
  }
  assert(op[i - 1].i.code == IRet);
  verify(L, op, op + from, op + to - 1, postable, rule);
}