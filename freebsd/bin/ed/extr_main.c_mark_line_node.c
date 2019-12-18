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
typedef  int /*<<< orphan*/  line_t ;

/* Variables and functions */
 int ERR ; 
 char* errmsg ; 
 int /*<<< orphan*/  islower (unsigned char) ; 
 int /*<<< orphan*/ ** mark ; 
 int /*<<< orphan*/  markno ; 

int
mark_line_node(line_t *lp, int n)
{
	if (!islower((unsigned char)n)) {
		errmsg = "invalid mark character";
		return ERR;
	} else if (mark[n - 'a'] == NULL)
		markno++;
	mark[n - 'a'] = lp;
	return 0;
}