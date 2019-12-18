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
struct TYPE_7__ {int len; scalar_t__ pdata; } ;
struct TYPE_5__ {int /*<<< orphan*/  str; } ;
typedef  int /*<<< orphan*/  GString ;
typedef  TYPE_3__ GPtrArray ;

/* Variables and functions */
 int /*<<< orphan*/  COM_INIT_DB ; 
 char COM_QUERY ; 
 scalar_t__ TK_COMMENT ; 
 scalar_t__ TK_LITERAL ; 
 scalar_t__ TK_SQL_USE ; 
 int /*<<< orphan*/  g_string_append_c (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_append_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_string_truncate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

GString* convert_use_database2com_init_db(char type, GString *origin_packets, GPtrArray *tokens) {
    if (type == COM_QUERY) { 
        sql_token **ts = (sql_token**)(tokens->pdata);
        guint tokens_len = tokens->len;
        if (tokens_len > 1) {
            guint i = 1;
            sql_token_id token_id = ts[i]->token_id;

            while (token_id == TK_COMMENT && ++i < tokens_len) {
                token_id = ts[i]->token_id;
            }

            if (token_id == TK_SQL_USE && (i+1) < tokens_len && ts[i+1]->token_id == TK_LITERAL) {
                g_string_truncate(origin_packets, 0);
                g_string_append_c(origin_packets, COM_INIT_DB);
                g_string_append_printf(origin_packets, "%s", ts[i+1]->text->str);
            }
        }
    }
    
    return origin_packets;
}