#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ sql_token_id ;
struct TYPE_4__ {scalar_t__ token_id; TYPE_3__* text; } ;
typedef  TYPE_1__ sql_token ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {int /*<<< orphan*/  str; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ TK_LITERAL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_string_ascii_up (TYPE_3__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

gboolean sql_token_equal(sql_token *token, sql_token_id token_id, const char *text)
{
	if( token->token_id != token_id)
		return FALSE;
	if(token_id == TK_LITERAL) {
		g_string_ascii_up(token->text);
		if( 0 != strcmp(token->text->str, text) ) 
			return FALSE;
	}
	return TRUE;
}