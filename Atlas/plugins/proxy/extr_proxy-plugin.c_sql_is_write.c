#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sql_token_id ;
struct TYPE_4__ {scalar_t__ token_id; } ;
typedef  TYPE_1__ sql_token ;
typedef  int guint ;
typedef  int gboolean ;
struct TYPE_5__ {int len; scalar_t__ pdata; } ;
typedef  TYPE_2__ GPtrArray ;

/* Variables and functions */
 scalar_t__ TK_COMMENT ; 
 scalar_t__ TK_SQL_DESC ; 
 scalar_t__ TK_SQL_EXPLAIN ; 
 scalar_t__ TK_SQL_SELECT ; 
 scalar_t__ TK_SQL_USE ; 
 int TRUE ; 

gboolean sql_is_write(GPtrArray *tokens) {
	sql_token **ts = (sql_token**)(tokens->pdata);
	guint len = tokens->len;

	if (len > 1) {
		guint i = 1;
		sql_token_id token_id = ts[i]->token_id;

		while (token_id == TK_COMMENT && ++i < len) {
			token_id = ts[i]->token_id;
		}

        // "set autocommit = 0; or show variables" need send to master
		return (token_id != TK_SQL_SELECT /*&& token_id != TK_SQL_SET */ && token_id != TK_SQL_USE /*&& token_id != TK_SQL_SHOW*/ && token_id != TK_SQL_DESC && token_id != TK_SQL_EXPLAIN);
	}

	return TRUE;
}