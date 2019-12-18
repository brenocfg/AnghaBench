#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sql_token_id ;
struct TYPE_6__ {scalar_t__ token_id; TYPE_1__* text; } ;
typedef  TYPE_2__ sql_token ;
typedef  int guint ;
typedef  int gint ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_7__ {int len; scalar_t__ pdata; } ;
struct TYPE_5__ {int /*<<< orphan*/ * str; } ;
typedef  TYPE_3__ GPtrArray ;

/* Variables and functions */
 scalar_t__ TK_COMMENT ; 
 scalar_t__ TK_DOT ; 
 scalar_t__ TK_FUNCTION ; 
 scalar_t__ TK_LITERAL ; 
 scalar_t__ TK_OBRACE ; 
 scalar_t__ TK_SQL_DELETE ; 
 scalar_t__ TK_SQL_FROM ; 
 scalar_t__ TK_SQL_INSERT ; 
 scalar_t__ TK_SQL_REPLACE ; 
 scalar_t__ TK_SQL_SELECT ; 
 scalar_t__ TK_SQL_SET ; 
 scalar_t__ TK_SQL_UPDATE ; 
 scalar_t__ TK_SQL_WHERE ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ *,char*) ; 

guint get_table_index(GPtrArray* tokens, gint* d, gint* t) {
	*d = *t = -1;

	sql_token** ts = (sql_token**)(tokens->pdata);
	guint len = tokens->len;
	if (len <= 1) { return 0; }

	guint i = 1, j;
	while (ts[i]->token_id == TK_COMMENT && ++i < len);
	if (i >= len) { return 0; } // sql contains TK_COMMENT only.

	sql_token_id token_id = ts[i]->token_id;

	if (token_id == TK_SQL_SELECT || token_id == TK_SQL_DELETE) {
		for (; i < len; ++i) {
			if (ts[i]->token_id == TK_SQL_FROM) {
				for (j = i+1; j < len; ++j) {
					if (ts[j]->token_id == TK_SQL_WHERE) break;

					if (ts[j]->token_id == TK_LITERAL) {
						if (j + 2 < len && ts[j+1]->token_id == TK_DOT) {
							*d = j;
							*t = j + 2;
						} else {
							*t = j;
						}

						break;
					}
				}

				break;
			}
		}

		return 1;
	} else if (token_id == TK_SQL_UPDATE) {
		for (; i < len; ++i) {
			if (ts[i]->token_id == TK_SQL_SET) break;

			if (ts[i]->token_id == TK_LITERAL) {
				if (i + 2 < len && ts[i+1]->token_id == TK_DOT) {
					*d = i;
					*t = i + 2;
				} else {
					*t = i;
				}

				break;
			}
		}

		return 2;
	} else if (token_id == TK_SQL_INSERT || token_id == TK_SQL_REPLACE) {
		for (; i < len; ++i) {
			gchar* str = ts[i]->text->str;
			if (strcasecmp(str, "VALUES") == 0 || strcasecmp(str, "VALUE") == 0) break;

			sql_token_id token_id = ts[i]->token_id;
			if (token_id == TK_LITERAL && i + 2 < len && ts[i+1]->token_id == TK_DOT) {
				*d = i;
				*t = i + 2;
				break;
			} else if (token_id == TK_LITERAL || token_id == TK_FUNCTION) {
				if (i == len - 1) {
					*t = i;
					break;
				} else {
					str = ts[i+1]->text->str;
					token_id = ts[i+1]->token_id;
					if (strcasecmp(str, "VALUES") == 0 || strcasecmp(str, "VALUE") == 0 || token_id == TK_OBRACE || token_id == TK_SQL_SET) {
						*t = i;
						break;
					}
				}
			}
		}

		return 3;
	}

	return 0;
}