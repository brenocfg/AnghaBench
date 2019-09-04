#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_Number ;
struct TYPE_2__ {int /*<<< orphan*/  len; } ;
typedef  int /*<<< orphan*/  const TValue ;

/* Variables and functions */
 scalar_t__ luaO_str2d (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  setnvalue (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svalue (int /*<<< orphan*/  const*) ; 
 TYPE_1__* tsvalue (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisnumber (int /*<<< orphan*/  const*) ; 
 scalar_t__ ttisstring (int /*<<< orphan*/  const*) ; 

const TValue *luaV_tonumber (const TValue *obj, TValue *n) {
  lua_Number num;
  if (ttisnumber(obj)) return obj;
  if (ttisstring(obj) && luaO_str2d(svalue(obj), tsvalue(obj)->len, &num)) {
    setnvalue(n, num);
    return n;
  }
  else
    return NULL;
}