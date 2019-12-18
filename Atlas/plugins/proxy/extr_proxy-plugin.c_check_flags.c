#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ token_id; TYPE_1__* text; } ;
typedef  TYPE_2__ sql_token ;
struct TYPE_9__ {int /*<<< orphan*/  is_in_select_calc_found_rows; int /*<<< orphan*/  locks; } ;
typedef  TYPE_3__ network_mysqld_con ;
typedef  int guint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_10__ {int len; scalar_t__ pdata; } ;
struct TYPE_7__ {int /*<<< orphan*/ * str; } ;
typedef  TYPE_4__ GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TK_SQL_SELECT ; 
 scalar_t__ TK_SQL_SQL_CALC_FOUND_ROWS ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_hash_table_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_lookup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_strdup (int /*<<< orphan*/ *) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 

void check_flags(GPtrArray* tokens, network_mysqld_con* con) {
	con->is_in_select_calc_found_rows = FALSE;

	sql_token** ts = (sql_token**)(tokens->pdata);
	guint len = tokens->len;

	if (len > 2) {
		if (ts[1]->token_id == TK_SQL_SELECT && strcasecmp(ts[2]->text->str, "GET_LOCK") == 0) {
			gchar* key = ts[4]->text->str;
			if (!g_hash_table_lookup(con->locks, key)) g_hash_table_add(con->locks, g_strdup(key));
		}

		/* if (len > 4) {	//SET AUTOCOMMIT = {0 | 1} */
		/* 	if (ts[1]->token_id == TK_SQL_SET && ts[3]->token_id == TK_EQ) { */
		/* 		if (strcasecmp(ts[2]->text->str, "AUTOCOMMIT") == 0) { */
		/* 			/1* char* str = ts[4]->text->str; *1/ */
		/* 			/1* if (strcmp(str, "0") == 0) con->is_not_autocommit = TRUE; *1/ */
		/* 			/1* else if (strcmp(str, "1") == 0) con->is_not_autocommit = FALSE; *1/ */
		/* 		} */
		/* 	} */
		/* } */
	}

	guint i;
	for (i = 1; i < len; ++i) {
		sql_token* token = ts[i];
		if (ts[i]->token_id == TK_SQL_SQL_CALC_FOUND_ROWS) {
			con->is_in_select_calc_found_rows = TRUE;
			break;
		}
	}
}