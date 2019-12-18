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
struct stackmark {int dummy; } ;
struct nodelist {int dummy; } ;

/* Variables and functions */
 int EXP_CASE ; 
 int EXP_TILDE ; 
 int /*<<< orphan*/  STARTSTACKSTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STPUTC (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  argstr (int /*<<< orphan*/ ,struct nodelist**,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  expdest ; 
 char* grabstackstr (int /*<<< orphan*/ ) ; 
 int patmatch (char*,char const*) ; 
 int /*<<< orphan*/  popstackmark (struct stackmark*) ; 
 int /*<<< orphan*/  setstackmark (struct stackmark*) ; 

int
casematch(union node *pattern, const char *val)
{
	struct stackmark smark;
	struct nodelist *argbackq;
	int result;
	char *p;

	setstackmark(&smark);
	argbackq = pattern->narg.backquote;
	STARTSTACKSTR(expdest);
	argstr(pattern->narg.text, &argbackq, EXP_TILDE | EXP_CASE, NULL);
	STPUTC('\0', expdest);
	p = grabstackstr(expdest);
	result = patmatch(p, val);
	popstackmark(&smark);
	return result;
}