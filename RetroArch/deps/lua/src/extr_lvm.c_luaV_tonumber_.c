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
typedef  int /*<<< orphan*/  lua_Number ;
typedef  int /*<<< orphan*/  TValue ;

/* Variables and functions */
 int /*<<< orphan*/  cast_num (int /*<<< orphan*/ ) ; 
 scalar_t__ cvt2num (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ivalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ luaO_str2num (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvalue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisinteger (int /*<<< orphan*/  const*) ; 
 scalar_t__ vslen (int /*<<< orphan*/  const*) ; 

int luaV_tonumber_ (const TValue *obj, lua_Number *n) {
  TValue v;
  if (ttisinteger(obj)) {
    *n = cast_num(ivalue(obj));
    return 1;
  }
  else if (cvt2num(obj) &&  /* string convertible to number? */
            luaO_str2num(svalue(obj), &v) == vslen(obj) + 1) {
    *n = nvalue(&v);  /* convert result of 'luaO_str2num' to a float */
    return 1;
  }
  else
    return 0;  /* conversion failed */
}