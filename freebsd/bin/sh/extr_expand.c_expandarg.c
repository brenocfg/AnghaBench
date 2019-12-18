#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  text; struct nodelist* backquote; } ;
union node {TYPE_1__ narg; } ;
struct worddest {scalar_t__ state; struct arglist* list; } ;
struct nodelist {int dummy; } ;
struct arglist {int dummy; } ;

/* Variables and functions */
 int EXP_GLOB ; 
 int EXP_SPLIT ; 
 int /*<<< orphan*/  STACKSTRNUL (scalar_t__) ; 
 int /*<<< orphan*/  STARTSTACKSTR (scalar_t__) ; 
 int /*<<< orphan*/  STPUTC (char,scalar_t__) ; 
 scalar_t__ WORD_IDLE ; 
 scalar_t__ WORD_QUOTEMARK ; 
 int /*<<< orphan*/  appendarglist (struct arglist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argstr (int /*<<< orphan*/ ,struct nodelist**,int,struct worddest*) ; 
 int /*<<< orphan*/  expandmeta (int /*<<< orphan*/ ,struct arglist*) ; 
 scalar_t__ expdest ; 
 scalar_t__ fflag ; 
 int /*<<< orphan*/  grabstackstr (scalar_t__) ; 
 scalar_t__ stackblock () ; 

void
expandarg(union node *arg, struct arglist *arglist, int flag)
{
	struct worddest exparg;
	struct nodelist *argbackq;

	if (fflag)
		flag &= ~EXP_GLOB;
	argbackq = arg->narg.backquote;
	exparg.list = arglist;
	exparg.state = WORD_IDLE;
	STARTSTACKSTR(expdest);
	argstr(arg->narg.text, &argbackq, flag, &exparg);
	if (arglist == NULL) {
		STACKSTRNUL(expdest);
		return;			/* here document expanded */
	}
	if ((flag & EXP_SPLIT) == 0 || expdest != stackblock() ||
	    exparg.state == WORD_QUOTEMARK) {
		STPUTC('\0', expdest);
		if (flag & EXP_SPLIT) {
			if (flag & EXP_GLOB)
				expandmeta(grabstackstr(expdest), exparg.list);
			else
				appendarglist(exparg.list, grabstackstr(expdest));
		}
	}
	if ((flag & EXP_SPLIT) == 0)
		appendarglist(arglist, grabstackstr(expdest));
}