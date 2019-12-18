#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pattern_t ;
struct TYPE_5__ {int /*<<< orphan*/  len; struct TYPE_5__* q_forw; } ;
typedef  TYPE_1__ line_t ;

/* Variables and functions */
 int ERR ; 
 int /*<<< orphan*/  NUL_TO_NEWLINE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_active_list () ; 
 char* errmsg ; 
 long first_addr ; 
 TYPE_1__* get_addressed_line_node (long) ; 
 int /*<<< orphan*/ * get_compiled_pattern () ; 
 char* get_sbuf_line (TYPE_1__*) ; 
 char* ibufp ; 
 scalar_t__ isbinary ; 
 int regexec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 long second_addr ; 
 scalar_t__ set_active_node (TYPE_1__*) ; 

int
build_active_list(int isgcmd)
{
	pattern_t *pat;
	line_t *lp;
	long n;
	char *s;
	char delimiter;

	if ((delimiter = *ibufp) == ' ' || delimiter == '\n') {
		errmsg = "invalid pattern delimiter";
		return ERR;
	} else if ((pat = get_compiled_pattern()) == NULL)
		return ERR;
	else if (*ibufp == delimiter)
		ibufp++;
	clear_active_list();
	lp = get_addressed_line_node(first_addr);
	for (n = first_addr; n <= second_addr; n++, lp = lp->q_forw) {
		if ((s = get_sbuf_line(lp)) == NULL)
			return ERR;
		if (isbinary)
			NUL_TO_NEWLINE(s, lp->len);
		if (!(regexec(pat, s, 0, NULL, 0) == isgcmd) &&
		    set_active_node(lp) < 0)
			return ERR;
	}
	return 0;
}