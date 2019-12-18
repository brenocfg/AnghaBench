#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct worddest {scalar_t__ state; TYPE_1__* list; } ;
struct TYPE_3__ {int /*<<< orphan*/  count; } ;

/* Variables and functions */
 int EXP_GLOB ; 
 int /*<<< orphan*/  STARTSTACKSTR (char*) ; 
 int /*<<< orphan*/  STPUTC (char,char*) ; 
 scalar_t__ WORD_IDLE ; 
 scalar_t__ WORD_QUOTEMARK ; 
 scalar_t__ WORD_WS_DELIMITED ; 
 int /*<<< orphan*/  appendarglist (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expandmeta (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * grabstackstr (char*) ; 
 char* stackblock () ; 

__attribute__((used)) static char *
nextword(char c, int flag, char *p, struct worddest *dst)
{
	int is_ws;

	is_ws = c == '\t' || c == '\n' || c == ' ';
	if (p != stackblock() || (is_ws ? dst->state == WORD_QUOTEMARK :
	    dst->state != WORD_WS_DELIMITED) || c == '\0') {
		STPUTC('\0', p);
		if (flag & EXP_GLOB)
			expandmeta(grabstackstr(p), dst->list);
		else
			appendarglist(dst->list, grabstackstr(p));
		dst->state = is_ws ? WORD_WS_DELIMITED : WORD_IDLE;
	} else if (!is_ws && dst->state == WORD_WS_DELIMITED)
		dst->state = WORD_IDLE;
	/* Reserve space while the stack string is empty. */
	appendarglist(dst->list, NULL);
	dst->list->count--;
	STARTSTACKSTR(p);
	return p;
}