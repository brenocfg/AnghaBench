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
struct parse_opt_ctx_t {int flags; char const* opt; char** argv; char** out; int /*<<< orphan*/  cpidx; scalar_t__ argc; } ;
struct option {int dummy; } ;

/* Variables and functions */
 int PARSE_OPT_DONE ; 
 int PARSE_OPT_KEEP_DASHDASH ; 
 int PARSE_OPT_KEEP_UNKNOWN ; 
 int PARSE_OPT_LIST ; 
 int PARSE_OPT_NO_INTERNAL_HELP ; 
 int PARSE_OPT_STOP_AT_NON_OPTION ; 
 int PARSE_OPT_UNKNOWN ; 
 int /*<<< orphan*/  check_typos (char const*,struct option const*) ; 
 int parse_long_opt (struct parse_opt_ctx_t*,char const*,struct option const*) ; 
 int parse_options_usage (char const* const*,struct option const*) ; 
 int parse_short_opt (struct parse_opt_ctx_t*,struct option const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 char* strdup (char*) ; 
 int usage_with_options_internal (char const* const*,struct option const*,int) ; 

int parse_options_step(struct parse_opt_ctx_t *ctx,
		       const struct option *options,
		       const char * const usagestr[])
{
	int internal_help = !(ctx->flags & PARSE_OPT_NO_INTERNAL_HELP);

	/* we must reset ->opt, unknown short option leave it dangling */
	ctx->opt = NULL;

	for (; ctx->argc; ctx->argc--, ctx->argv++) {
		const char *arg = ctx->argv[0];

		if (*arg != '-' || !arg[1]) {
			if (ctx->flags & PARSE_OPT_STOP_AT_NON_OPTION)
				break;
			ctx->out[ctx->cpidx++] = ctx->argv[0];
			continue;
		}

		if (arg[1] != '-') {
			ctx->opt = arg + 1;
			if (internal_help && *ctx->opt == 'h')
				return parse_options_usage(usagestr, options);
			switch (parse_short_opt(ctx, options)) {
			case -1:
				return parse_options_usage(usagestr, options);
			case -2:
				goto unknown;
			default:
				break;
			}
			if (ctx->opt)
				check_typos(arg + 1, options);
			while (ctx->opt) {
				if (internal_help && *ctx->opt == 'h')
					return parse_options_usage(usagestr, options);
				switch (parse_short_opt(ctx, options)) {
				case -1:
					return parse_options_usage(usagestr, options);
				case -2:
					/* fake a short option thing to hide the fact that we may have
					 * started to parse aggregated stuff
					 *
					 * This is leaky, too bad.
					 */
					ctx->argv[0] = strdup(ctx->opt - 1);
					*(char *)ctx->argv[0] = '-';
					goto unknown;
				default:
					break;
				}
			}
			continue;
		}

		if (!arg[2]) { /* "--" */
			if (!(ctx->flags & PARSE_OPT_KEEP_DASHDASH)) {
				ctx->argc--;
				ctx->argv++;
			}
			break;
		}

		if (internal_help && !strcmp(arg + 2, "help-all"))
			return usage_with_options_internal(usagestr, options, 1);
		if (internal_help && !strcmp(arg + 2, "help"))
			return parse_options_usage(usagestr, options);
		if (!strcmp(arg + 2, "list-opts"))
			return PARSE_OPT_LIST;
		switch (parse_long_opt(ctx, arg + 2, options)) {
		case -1:
			return parse_options_usage(usagestr, options);
		case -2:
			goto unknown;
		default:
			break;
		}
		continue;
unknown:
		if (!(ctx->flags & PARSE_OPT_KEEP_UNKNOWN))
			return PARSE_OPT_UNKNOWN;
		ctx->out[ctx->cpidx++] = ctx->argv[0];
		ctx->opt = NULL;
	}
	return PARSE_OPT_DONE;
}