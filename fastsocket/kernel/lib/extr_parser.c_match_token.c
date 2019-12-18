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
typedef  int /*<<< orphan*/  substring_t ;
struct match_token {int token; int /*<<< orphan*/  pattern; } ;
typedef  struct match_token* match_table_t ;

/* Variables and functions */
 int /*<<< orphan*/  match_one (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int match_token(char *s, const match_table_t table, substring_t args[])
{
	const struct match_token *p;

	for (p = table; !match_one(s, p->pattern, args) ; p++)
		;

	return p->token;
}