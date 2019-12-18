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
struct parse_opt_ctx_t {int argc; char const** argv; char const** out; int cpidx; int flags; } ;

/* Variables and functions */
 int PARSE_OPT_KEEP_ARGV0 ; 
 int PARSE_OPT_KEEP_UNKNOWN ; 
 int PARSE_OPT_STOP_AT_NON_OPTION ; 
 int /*<<< orphan*/  die (char*) ; 
 int /*<<< orphan*/  memset (struct parse_opt_ctx_t*,int /*<<< orphan*/ ,int) ; 

void parse_options_start(struct parse_opt_ctx_t *ctx,
			 int argc, const char **argv, int flags)
{
	memset(ctx, 0, sizeof(*ctx));
	ctx->argc = argc - 1;
	ctx->argv = argv + 1;
	ctx->out  = argv;
	ctx->cpidx = ((flags & PARSE_OPT_KEEP_ARGV0) != 0);
	ctx->flags = flags;
	if ((flags & PARSE_OPT_KEEP_UNKNOWN) &&
	    (flags & PARSE_OPT_STOP_AT_NON_OPTION))
		die("STOP_AT_NON_OPTION and KEEP_UNKNOWN don't go together");
}