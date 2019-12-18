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
struct parse_opt_ctx_t {char** argv; int /*<<< orphan*/ * opt; } ;
struct option {char* long_name; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  OPTION_END ; 
#define  PARSE_OPT_DONE 130 
#define  PARSE_OPT_HELP 129 
#define  PARSE_OPT_LIST 128 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int parse_options_end (struct parse_opt_ctx_t*) ; 
 int /*<<< orphan*/  parse_options_start (struct parse_opt_ctx_t*,int,char const**,int) ; 
 int parse_options_step (struct parse_opt_ctx_t*,struct option const*,char const* const*) ; 
 int /*<<< orphan*/  perf_header__set_cmdline (int,char const**) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  usage_with_options (char const* const*,struct option const*) ; 

int parse_options(int argc, const char **argv, const struct option *options,
		  const char * const usagestr[], int flags)
{
	struct parse_opt_ctx_t ctx;

	perf_header__set_cmdline(argc, argv);

	parse_options_start(&ctx, argc, argv, flags);
	switch (parse_options_step(&ctx, options, usagestr)) {
	case PARSE_OPT_HELP:
		exit(129);
	case PARSE_OPT_DONE:
		break;
	case PARSE_OPT_LIST:
		while (options->type != OPTION_END) {
			printf("--%s ", options->long_name);
			options++;
		}
		exit(130);
	default: /* PARSE_OPT_UNKNOWN */
		if (ctx.argv[0][1] == '-') {
			error("unknown option `%s'", ctx.argv[0] + 2);
		} else {
			error("unknown switch `%c'", *ctx.opt);
		}
		usage_with_options(usagestr, options);
	}

	return parse_options_end(&ctx);
}