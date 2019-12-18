#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_5__ {int /*<<< orphan*/  code; } ;
struct TYPE_6__ {scalar_t__* buff; TYPE_1__ i; } ;
typedef  TYPE_2__ Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  CHARSETINSTSIZE ; 
 int /*<<< orphan*/  ISet ; 
 size_t i ; 
 int /*<<< orphan*/  loopset (size_t,scalar_t__) ; 
 TYPE_2__* newpatt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static Instruction *newcharset (lua_State *L) {
  Instruction *p = newpatt(L, CHARSETINSTSIZE);
  p[0].i.code = ISet;
  loopset(i, p[1].buff[i] = 0);
  return p;
}