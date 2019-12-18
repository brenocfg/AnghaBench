#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sql_token_id ;
struct TYPE_10__ {scalar_t__ token_id; TYPE_1__* text; } ;
typedef  TYPE_2__ sql_token ;
struct TYPE_11__ {int /*<<< orphan*/  locks; } ;
typedef  TYPE_3__ network_mysqld_con ;
struct TYPE_12__ {int len; TYPE_2__** pdata; } ;
struct TYPE_9__ {int /*<<< orphan*/  str; } ;
typedef  TYPE_4__ GPtrArray ;

/* Variables and functions */
 scalar_t__ TK_COMMENT ; 
 scalar_t__ g_hash_table_size (int /*<<< orphan*/ ) ; 
 int idle_rw (TYPE_3__*) ; 
 scalar_t__ strcasecmp (int /*<<< orphan*/ ,char*) ; 
 int wrr_ro (TYPE_3__*) ; 

int rw_split(GPtrArray* tokens, network_mysqld_con* con) {
	if (tokens->len <= 1) { return idle_rw(con); }

	sql_token* first_token = tokens->pdata[1];
	sql_token_id token_id = first_token->token_id;
	if (token_id == TK_COMMENT && strcasecmp(first_token->text->str, "MASTER") == 0) return idle_rw(con);

	if (tokens->len < 2 || g_hash_table_size(con->locks) > 0) return idle_rw(con);

	return wrr_ro(con);
}