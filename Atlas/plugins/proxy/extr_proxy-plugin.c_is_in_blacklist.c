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
struct TYPE_6__ {scalar_t__ token_id; TYPE_1__* text; } ;
typedef  TYPE_2__ sql_token ;
typedef  int guint ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_7__ {int len; TYPE_2__** pdata; } ;
struct TYPE_5__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_3__ GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TK_OBRACE ; 
 scalar_t__ TK_SQL_DELETE ; 
 scalar_t__ TK_SQL_UPDATE ; 
 scalar_t__ TK_SQL_WHERE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 

gboolean is_in_blacklist(GPtrArray* tokens) {
	guint len = tokens->len;
	if (len > 1) {
		guint i;

		sql_token* token = tokens->pdata[1];
		if (token->token_id == TK_SQL_DELETE || token->token_id == TK_SQL_UPDATE) {
			for (i = 2; i < len; ++i) {
				token = tokens->pdata[i];
				if (token->token_id == TK_SQL_WHERE) break;
			}
			if (i == len) return TRUE;
		}

		for (i = 2; i < len; ++i) {
			token = tokens->pdata[i];
			if (token->token_id == TK_OBRACE) {
				token = tokens->pdata[i-1];
				if (strcasecmp(token->text->str, "SLEEP") == 0) return TRUE;
			}
		}
	}

	return FALSE;
}