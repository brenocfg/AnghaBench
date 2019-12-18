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
struct TYPE_3__ {char* name; } ;
typedef  TYPE_1__ VAR ;

/* Variables and functions */
 int strlen (char const*) ; 
 int termwidth ; 
 TYPE_1__* var ; 
 int /*<<< orphan*/  xo_close_list (char*) ; 
 int /*<<< orphan*/  xo_emit (char*,...) ; 
 int /*<<< orphan*/  xo_finish () ; 
 int /*<<< orphan*/  xo_open_list (char*) ; 

void
showkey(void)
{
	VAR *v;
	int i;
	const char *p, *sep;

	i = 0;
	sep = "";
	xo_open_list("key");
	for (v = var; *(p = v->name); ++v) {
		int len = strlen(p);
		if (termwidth && (i += len + 1) > termwidth) {
			i = len;
			sep = "\n";
		}
		xo_emit("{P:/%s}{l:key/%s}", sep, p);
		sep = " ";
	}
	xo_emit("\n");
	xo_close_list("key");
	xo_finish();
}