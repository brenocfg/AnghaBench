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
struct TYPE_4__ {int /*<<< orphan*/  type; void* name; } ;
typedef  TYPE_1__ MYSQL_FIELD ;
typedef  int /*<<< orphan*/  GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/  FIELD_TYPE_VAR_STRING ; 
 int /*<<< orphan*/  g_ptr_array_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 void* g_strdup (char*) ; 
 void* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* network_mysqld_proto_fielddef_new () ; 

__attribute__((used)) static int lua_table_key_to_mysql_field(lua_State *L, GPtrArray *fields) {
	MYSQL_FIELD *field = NULL;

	field = network_mysqld_proto_fielddef_new();
	if (lua_isstring(L, -2) && !lua_isnumber(L, -2)) {
		/* is-string is true for strings AND numbers
		 * but a tostring() is changing a number into a 
		 * string and that trashes the lua_next() call
		 */
		field->name = g_strdup(lua_tostring(L, -2));
	} else if (lua_isnumber(L, -2)) {
		field->name = g_strdup_printf("%ld", lua_tointeger(L, -2));
	} else {
		/* we don't know how to convert the key */
		field->name = g_strdup("(hmm)");
	}
	field->type = FIELD_TYPE_VAR_STRING; /* STRING matches all values */
	g_ptr_array_add(fields, field);

	return 0;
}