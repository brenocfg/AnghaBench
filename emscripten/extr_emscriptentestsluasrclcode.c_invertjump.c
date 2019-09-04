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
struct TYPE_4__ {int /*<<< orphan*/  info; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ expdesc ;
typedef  int /*<<< orphan*/  Instruction ;
typedef  int /*<<< orphan*/  FuncState ;

/* Variables and functions */
 int /*<<< orphan*/  GETARG_A (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_OPCODE (int /*<<< orphan*/ ) ; 
 scalar_t__ OP_TEST ; 
 scalar_t__ OP_TESTSET ; 
 int /*<<< orphan*/  SETARG_A (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * getjumpcontrol (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_assert (int) ; 
 scalar_t__ testTMode (scalar_t__) ; 

__attribute__((used)) static void invertjump (FuncState *fs, expdesc *e) {
  Instruction *pc = getjumpcontrol(fs, e->u.info);
  lua_assert(testTMode(GET_OPCODE(*pc)) && GET_OPCODE(*pc) != OP_TESTSET &&
                                           GET_OPCODE(*pc) != OP_TEST);
  SETARG_A(*pc, !(GETARG_A(*pc)));
}