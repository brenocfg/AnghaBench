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
struct parse_opt_ctx_t {char* opt; int argc; char** argv; } ;
struct option {int flags; scalar_t__ defval; } ;

/* Variables and functions */
 int PARSE_OPT_LASTARG_DEFAULT ; 
 int opterror (struct option const*,char*,int) ; 

__attribute__((used)) static int get_arg(struct parse_opt_ctx_t *p, const struct option *opt,
		   int flags, const char **arg)
{
	if (p->opt) {
		*arg = p->opt;
		p->opt = NULL;
	} else if ((opt->flags & PARSE_OPT_LASTARG_DEFAULT) && (p->argc == 1 ||
		    **(p->argv + 1) == '-')) {
		*arg = (const char *)opt->defval;
	} else if (p->argc > 1) {
		p->argc--;
		*arg = *++p->argv;
	} else
		return opterror(opt, "requires a value", flags);
	return 0;
}