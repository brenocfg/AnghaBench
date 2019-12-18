#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* t; } ;
typedef  TYPE_1__ undo_t ;
struct TYPE_6__ {struct TYPE_6__* q_forw; } ;
typedef  TYPE_2__ line_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 long ERR ; 
 int /*<<< orphan*/  SPL0 () ; 
 int /*<<< orphan*/  SPL1 () ; 
 int /*<<< orphan*/  UADD ; 
 long addr_last ; 
 long current_addr ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ ) ; 
 TYPE_2__* get_addressed_line_node (long) ; 
 int get_stream_line (int /*<<< orphan*/ *) ; 
 int isbinary ; 
 int newline_added ; 
 TYPE_1__* push_undo_stack (int /*<<< orphan*/ ,long,long) ; 
 int /*<<< orphan*/ * put_sbuf_line (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sbuf ; 
 int /*<<< orphan*/  stderr ; 

long
read_stream(FILE *fp, long n)
{
	line_t *lp = get_addressed_line_node(n);
	undo_t *up = NULL;
	unsigned long size = 0;
	int o_newline_added = newline_added;
	int o_isbinary = isbinary;
	int appended = (n == addr_last);
	int len;

	isbinary = newline_added = 0;
	for (current_addr = n; (len = get_stream_line(fp)) > 0; size += len) {
		SPL1();
		if (put_sbuf_line(sbuf) == NULL) {
			SPL0();
			return ERR;
		}
		lp = lp->q_forw;
		if (up)
			up->t = lp;
		else if ((up = push_undo_stack(UADD, current_addr,
		    current_addr)) == NULL) {
			SPL0();
			return ERR;
		}
		SPL0();
	}
	if (len < 0)
		return ERR;
	if (appended && size && o_isbinary && o_newline_added)
		fputs("newline inserted\n", stderr);
	else if (newline_added && (!appended || (!isbinary && !o_isbinary)))
		fputs("newline appended\n", stderr);
	if (isbinary && newline_added && !appended)
	    	size += 1;
	if (!size)
		newline_added = 1;
	newline_added = appended ? newline_added : o_newline_added;
	isbinary = isbinary | o_isbinary;
	return size;
}