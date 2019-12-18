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
typedef  int /*<<< orphan*/  libretrodb_cursor_t ;

/* Variables and functions */
 int /*<<< orphan*/ * checkcursor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  libretrodb_cursor_close (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int cursor_close(lua_State *L)
{
	libretrodb_cursor_t *cursor = checkcursor(L);
	libretrodb_cursor_close(cursor);
	return 0;
}