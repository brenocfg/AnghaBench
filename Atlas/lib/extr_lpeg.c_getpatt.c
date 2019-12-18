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
 int /*<<< orphan*/  Cclose ; 
 int /*<<< orphan*/  Cruntime ; 
 int /*<<< orphan*/  IChar ; 
 int /*<<< orphan*/  IChoice ; 
 int /*<<< orphan*/  ICloseRunTime ; 
 int /*<<< orphan*/  IFail ; 
 int /*<<< orphan*/  IFailTwice ; 
 int /*<<< orphan*/  IOpenCapture ; 
 int /*<<< orphan*/  ITestAny ; 
#define  LUA_TBOOLEAN 132 
#define  LUA_TFUNCTION 131 
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int UCHAR_MAX ; 
 int /*<<< orphan*/ * any (int /*<<< orphan*/ *,int,int,int*) ; 
 int /*<<< orphan*/ * checkpattern (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fix_l (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_replace (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * newpatt (int /*<<< orphan*/ *,int) ; 
 int pattsize (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  setinst (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setinstaux (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  setinstcap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  value2fenv (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static Instruction *getpatt (lua_State *L, int idx, int *size) {
  Instruction *p;
  switch (lua_type(L, idx)) {
    case LUA_TSTRING: {
      size_t i, len;
      const char *s = lua_tolstring(L, idx, &len);
      p = newpatt(L, len);
      for (i = 0; i < len; i++)
        setinstaux(p + i, IChar, 0, (unsigned char)s[i]);
      lua_replace(L, idx);
      break;
    }
    case LUA_TNUMBER: {
      int n = lua_tointeger(L, idx);
      if (n == 0)  /* empty pattern? */
        p = newpatt(L, 0);
      else if (n > 0)
        p = any(L, n, 0, NULL);
      else if (-n <= UCHAR_MAX) {
        p = newpatt(L, 2);
        setinstaux(p, ITestAny, 2, -n);
        setinst(p + 1, IFail, 0);
      }
      else {
        int offset = 2;  /* space for ITestAny & IChoice */
        p = any(L, -n - UCHAR_MAX, 3, &offset);
        setinstaux(p, ITestAny, offset + 1, UCHAR_MAX);
        setinstaux(p + 1, IChoice, offset, UCHAR_MAX);
        setinst(p + offset, IFailTwice, 0);
      }
      lua_replace(L, idx);
      break;
    }
    case LUA_TBOOLEAN: {
      if (lua_toboolean(L, idx))  /* true? */
        p = newpatt(L, 0);  /* empty pattern (always succeeds) */
      else {
        p = newpatt(L, 1);
        setinst(p, IFail, 0);
      }
      lua_replace(L, idx);
      break;
    }
    case LUA_TTABLE: {
      p = fix_l(L, idx);
      break;
    }
    case LUA_TFUNCTION: {
      p = newpatt(L, 2);
      setinstcap(p, IOpenCapture, value2fenv(L, idx), Cruntime, 0);
      setinstcap(p + 1, ICloseRunTime, 0, Cclose, 0);
      lua_replace(L, idx);
      break;
    }
    default: {
      p = checkpattern(L, idx);
      break;
    }
  }
  if (size) *size = pattsize(L, idx);
  return p;
}