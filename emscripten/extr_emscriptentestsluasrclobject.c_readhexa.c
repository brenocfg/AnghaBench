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
typedef  int lua_Number ;

/* Variables and functions */
 int cast_num (double) ; 
 int /*<<< orphan*/  cast_uchar (char const) ; 
 scalar_t__ lisxdigit (int /*<<< orphan*/ ) ; 
 double luaO_hexavalue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static lua_Number readhexa (const char **s, lua_Number r, int *count) {
  for (; lisxdigit(cast_uchar(**s)); (*s)++) {  /* read integer part */
    r = (r * cast_num(16.0)) + cast_num(luaO_hexavalue(cast_uchar(**s)));
    (*count)++;
  }
  return r;
}