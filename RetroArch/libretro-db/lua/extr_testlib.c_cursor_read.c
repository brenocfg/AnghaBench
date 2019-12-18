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
struct rmsgpack_dom_value {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  libretrodb_cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/ * checkcursor (int /*<<< orphan*/ *) ; 
 scalar_t__ libretrodb_cursor_read_item (int /*<<< orphan*/ *,struct rmsgpack_dom_value*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  push_rmsgpack_value (int /*<<< orphan*/ *,struct rmsgpack_dom_value*) ; 

__attribute__((used)) static int cursor_read(lua_State *L)
{
   libretrodb_cursor_t *cursor = checkcursor(L);
   struct rmsgpack_dom_value value;
   if (libretrodb_cursor_read_item(cursor, &value) == 0)
      push_rmsgpack_value(L, &value);
   else
      lua_pushnil(L);
   return 1;
}