#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pattern_t ;
struct TYPE_4__ {int /*<<< orphan*/  len; } ;
typedef  TYPE_1__ line_t ;

/* Variables and functions */
 long DEC_MOD (long,int /*<<< orphan*/ ) ; 
 long ERR ; 
 long INC_MOD (long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NUL_TO_NEWLINE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  addr_last ; 
 long current_addr ; 
 char* errmsg ; 
 TYPE_1__* get_addressed_line_node (long) ; 
 char* get_sbuf_line (TYPE_1__*) ; 
 scalar_t__ isbinary ; 
 int /*<<< orphan*/  regexec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

long
get_matching_node_addr(pattern_t *pat, int dir)
{
	char *s;
	long n = current_addr;
	line_t *lp;

	if (!pat) return ERR;
	do {
	       if ((n = dir ? INC_MOD(n, addr_last) : DEC_MOD(n, addr_last))) {
			lp = get_addressed_line_node(n);
			if ((s = get_sbuf_line(lp)) == NULL)
				return ERR;
			if (isbinary)
				NUL_TO_NEWLINE(s, lp->len);
			if (!regexec(pat, s, 0, NULL, 0))
				return n;
	       }
	} while (n != current_addr);
	errmsg = "no match";
	return  ERR;
}