#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int /*<<< orphan*/  buff; } ;
typedef  TYPE_1__ Instruction ;

/* Variables and functions */
 int /*<<< orphan*/  correctset (TYPE_1__*) ; 
 int /*<<< orphan*/  getpatt (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 char* luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 TYPE_1__* newcharset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setchar (int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static int set_l (lua_State *L) {
  size_t l;
  const char *s = luaL_checklstring(L, 1, &l);
  if (l == 1)
    getpatt(L, 1, NULL);  /* a unit set is equivalent to a literal */
  else {
    Instruction *p = newcharset(L);
    while (l--) {
      setchar(p[1].buff, (unsigned char)(*s));
      s++;
    }
    correctset(p);
  }
  return 1;
}