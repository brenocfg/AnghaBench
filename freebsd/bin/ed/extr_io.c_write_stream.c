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
struct TYPE_4__ {int len; struct TYPE_4__* q_forw; } ;
typedef  TYPE_1__ line_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 long ERR ; 
 long addr_last ; 
 TYPE_1__* get_addressed_line_node (long) ; 
 char* get_sbuf_line (TYPE_1__*) ; 
 int /*<<< orphan*/  isbinary ; 
 int /*<<< orphan*/  newline_added ; 
 scalar_t__ put_stream_line (int /*<<< orphan*/ *,char*,int) ; 

long
write_stream(FILE *fp, long n, long m)
{
	line_t *lp = get_addressed_line_node(n);
	unsigned long size = 0;
	char *s;
	int len;

	for (; n && n <= m; n++, lp = lp->q_forw) {
		if ((s = get_sbuf_line(lp)) == NULL)
			return ERR;
		len = lp->len;
		if (n != addr_last || !isbinary || !newline_added)
			s[len++] = '\n';
		if (put_stream_line(fp, s, len) < 0)
			return ERR;
		size += len;
	}
	return size;
}