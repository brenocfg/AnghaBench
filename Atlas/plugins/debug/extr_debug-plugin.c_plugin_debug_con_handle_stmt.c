#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_5__ ;
typedef  struct TYPE_26__   TYPE_4__ ;
typedef  struct TYPE_25__   TYPE_3__ ;
typedef  struct TYPE_24__   TYPE_2__ ;
typedef  struct TYPE_23__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  client; } ;
typedef  TYPE_2__ network_mysqld_con ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  size_t gsize ;
struct TYPE_25__ {TYPE_1__* sc; } ;
typedef  TYPE_3__ chassis ;
struct TYPE_27__ {int* str; } ;
struct TYPE_26__ {size_t len; struct TYPE_26__** pdata; void* type; struct TYPE_26__* name; } ;
struct TYPE_23__ {int /*<<< orphan*/ * L; } ;
typedef  TYPE_4__ MYSQL_FIELD ;
typedef  TYPE_5__ GString ;
typedef  TYPE_4__ GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/  C (char*) ; 
#define  COM_INIT_DB 131 
#define  COM_QUERY 130 
#define  COM_QUIT 129 
 void* FIELD_TYPE_VAR_STRING ; 
#define  LUA_TTABLE 128 
 size_t NET_HEADER_SIZE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_ascii_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (TYPE_4__*) ; 
 int /*<<< orphan*/  g_ptr_array_add (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  g_ptr_array_free (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_4__* g_ptr_array_new () ; 
 TYPE_4__* g_strdup (char*) ; 
 TYPE_4__* g_strdup_printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_loadstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_table_key_to_mysql_field (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  lua_toboolean (int /*<<< orphan*/ *,int) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int /*<<< orphan*/  lua_tonumber (int /*<<< orphan*/ *,int) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  network_mysqld_con_send_error (int /*<<< orphan*/ ,char const*,...) ; 
 int /*<<< orphan*/  network_mysqld_con_send_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  network_mysqld_con_send_resultset (int /*<<< orphan*/ ,TYPE_4__*,TYPE_4__*) ; 
 TYPE_4__* network_mysqld_proto_fielddef_new () ; 
 int /*<<< orphan*/  network_mysqld_proto_fielddefs_free (TYPE_4__*) ; 
 TYPE_4__* network_mysqld_proto_fielddefs_new () ; 

int plugin_debug_con_handle_stmt(chassis *chas, network_mysqld_con *con, GString *s) {
	gsize i, j;
	GPtrArray *fields;
	GPtrArray *rows;
	GPtrArray *row;

	switch(s->str[NET_HEADER_SIZE]) {
	case COM_QUERY:
		fields = NULL;
		rows = NULL;
		row = NULL;

		/* support the basic commands sent by the mysql shell */
		if (0 == g_ascii_strncasecmp(s->str + NET_HEADER_SIZE + 1, C("select @@version_comment limit 1"))) {
			MYSQL_FIELD *field;

			fields = network_mysqld_proto_fielddefs_new();

			field = network_mysqld_proto_fielddef_new();
			field->name = g_strdup("@@version_comment");
			field->type = FIELD_TYPE_VAR_STRING;
			g_ptr_array_add(fields, field);

			rows = g_ptr_array_new();
			row = g_ptr_array_new();
			g_ptr_array_add(row, g_strdup("MySQL Enterprise Agent"));
			g_ptr_array_add(rows, row);

			network_mysqld_con_send_resultset(con->client, fields, rows);
			
		} else if (0 == g_ascii_strncasecmp(s->str + NET_HEADER_SIZE + 1, C("select USER()"))) {
			MYSQL_FIELD *field;

			fields = network_mysqld_proto_fielddefs_new();
			field = network_mysqld_proto_fielddef_new();
			field->name = g_strdup("USER()");
			field->type = FIELD_TYPE_VAR_STRING;
			g_ptr_array_add(fields, field);

			rows = g_ptr_array_new();
			row = g_ptr_array_new();
			g_ptr_array_add(row, g_strdup("root"));
			g_ptr_array_add(rows, row);

			network_mysqld_con_send_resultset(con->client, fields, rows);
		} else {
			MYSQL_FIELD *field = NULL;
			lua_State *L = chas->sc->L;

			if (0 == luaL_loadstring(L, s->str + NET_HEADER_SIZE + 1) &&
			    0 == lua_pcall(L, 0, 1, 0)) {
				/* let's see what is on the stack
				 * - scalars are turned into strings
				 *   return "foo" 
				 * - 1-dim tables are turned into a single-row result-set
				 *   return { foo = "bar", baz = "foz" }
				 * - 2-dim tables are turned into a multi-row result-set
				 *   return { { foo = "bar" }, { "foz" } }
				 */
				switch (lua_type(L, -1)) {
				case LUA_TTABLE:
					/* take the names from the fields */
					fields = network_mysqld_proto_fielddefs_new();

					lua_pushnil(L);
					while (lua_next(L, -2) != 0) {
						if (lua_istable(L, -1)) {
							/* 2-dim table
							 * 
							 * we only only take the keys from the first row
							 * afterwards we ignore them
							 */
					
							lua_pushnil(L);
							while (lua_next(L, -2) != 0) {
								if (!rows) {
									/* this is the 1st round, add the keys */
									lua_table_key_to_mysql_field(L, fields);
								}

								if (!row) row = g_ptr_array_new();
								if (lua_isboolean(L, -1)) {
									g_ptr_array_add(row, g_strdup(lua_toboolean(L, -1) ? "TRUE" : "FALSE"));
								} else if (lua_isnumber(L, -1)) {
									g_ptr_array_add(row, g_strdup_printf("%.0f", lua_tonumber(L, -1)));
								} else {
									g_ptr_array_add(row, g_strdup(lua_tostring(L, -1)));
								}

								lua_pop(L, 1); /* pop the value, but keep the key on the stack */
							}
					
							if (!rows) rows = g_ptr_array_new();
							g_ptr_array_add(rows, row);

							row = NULL;
						} else {
							/* 1-dim table */
							lua_table_key_to_mysql_field(L, fields);

							if (!row) row = g_ptr_array_new();
							if (lua_isboolean(L, -1)) {
								g_ptr_array_add(row, g_strdup(lua_toboolean(L, -1) ? "TRUE" : "FALSE"));
							} else if (lua_isnumber(L, -1)) {
								g_ptr_array_add(row, g_strdup_printf("%.0f", lua_tonumber(L, -1)));
							} else {
								g_ptr_array_add(row, g_strdup(lua_tostring(L, -1)));
							}
						}

						lua_pop(L, 1); /* pop the value, but keep the key on the stack */
					}

					if (row) {
						/* in 1-dim we have to append the row to the result-set,
						 * in 2-dim this is already done and row is NULL */
						if (!rows) rows = g_ptr_array_new();
						g_ptr_array_add(rows, row);
					}

					break;
				default:
					/* a scalar value */
					fields = network_mysqld_proto_fielddefs_new();
					field = network_mysqld_proto_fielddef_new();
					field->name = g_strdup("lua");
					field->type = FIELD_TYPE_VAR_STRING;
					g_ptr_array_add(fields, field);
		
					rows = g_ptr_array_new();
					row = g_ptr_array_new();
					g_ptr_array_add(row, g_strdup(lua_tostring(L, -1)));
					g_ptr_array_add(rows, row);

					break;
				}

				lua_pop(L, 1); /* get rid of the result */

				network_mysqld_con_send_resultset(con->client, fields, rows);
			}

			/* if we don't have fields for the resultset, we should have a
			 * error-msg on the stack */
			if (!fields) {
				size_t err_len = 0;
				const char *err;

				err = lua_tolstring(L, -1, &err_len);

				network_mysqld_con_send_error(con->client, err, err_len);
				
				lua_pop(L, 1);
			}
		}

		/* clean up */
		if (fields) {
			network_mysqld_proto_fielddefs_free(fields);
			fields = NULL;
		}

		if (rows) {
			for (i = 0; i < rows->len; i++) {
				row = rows->pdata[i];

				for (j = 0; j < row->len; j++) {
					g_free(row->pdata[j]);
				}

				g_ptr_array_free(row, TRUE);
			}
			g_ptr_array_free(rows, TRUE);
			rows = NULL;
		}

		break;
	case COM_QUIT:
		break;
	case COM_INIT_DB:
		network_mysqld_con_send_ok(con->client);
		break;
	default:
		network_mysqld_con_send_error(con->client, C("unknown COM_*"));
		break;
	}

	return 0;
}