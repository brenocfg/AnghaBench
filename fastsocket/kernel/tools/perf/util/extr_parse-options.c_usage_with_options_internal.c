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
struct option {int type; char* help; int flags; int short_name; char* long_name; char* argh; } ;

/* Variables and functions */
#define  OPTION_ARGUMENT 141 
#define  OPTION_BIT 140 
#define  OPTION_BOOLEAN 139 
#define  OPTION_CALLBACK 138 
#define  OPTION_END 137 
#define  OPTION_GROUP 136 
#define  OPTION_INCR 135 
#define  OPTION_INTEGER 134 
#define  OPTION_LONG 133 
#define  OPTION_SET_PTR 132 
#define  OPTION_SET_UINT 131 
#define  OPTION_STRING 130 
#define  OPTION_U64 129 
#define  OPTION_UINTEGER 128 
 int PARSE_OPT_HELP ; 
 int PARSE_OPT_HIDDEN ; 
 int PARSE_OPT_NOARG ; 
 int PARSE_OPT_OPTARG ; 
 char* USAGE_GAP ; 
 size_t USAGE_OPTS_WIDTH ; 
 size_t fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

int usage_with_options_internal(const char * const *usagestr,
				const struct option *opts, int full)
{
	if (!usagestr)
		return PARSE_OPT_HELP;

	fprintf(stderr, "\n usage: %s\n", *usagestr++);
	while (*usagestr && **usagestr)
		fprintf(stderr, "    or: %s\n", *usagestr++);
	while (*usagestr) {
		fprintf(stderr, "%s%s\n",
				**usagestr ? "    " : "",
				*usagestr);
		usagestr++;
	}

	if (opts->type != OPTION_GROUP)
		fputc('\n', stderr);

	for (; opts->type != OPTION_END; opts++) {
		size_t pos;
		int pad;

		if (opts->type == OPTION_GROUP) {
			fputc('\n', stderr);
			if (*opts->help)
				fprintf(stderr, "%s\n", opts->help);
			continue;
		}
		if (!full && (opts->flags & PARSE_OPT_HIDDEN))
			continue;

		pos = fprintf(stderr, "    ");
		if (opts->short_name)
			pos += fprintf(stderr, "-%c", opts->short_name);
		else
			pos += fprintf(stderr, "    ");

		if (opts->long_name && opts->short_name)
			pos += fprintf(stderr, ", ");
		if (opts->long_name)
			pos += fprintf(stderr, "--%s", opts->long_name);

		switch (opts->type) {
		case OPTION_ARGUMENT:
			break;
		case OPTION_LONG:
		case OPTION_U64:
		case OPTION_INTEGER:
		case OPTION_UINTEGER:
			if (opts->flags & PARSE_OPT_OPTARG)
				if (opts->long_name)
					pos += fprintf(stderr, "[=<n>]");
				else
					pos += fprintf(stderr, "[<n>]");
			else
				pos += fprintf(stderr, " <n>");
			break;
		case OPTION_CALLBACK:
			if (opts->flags & PARSE_OPT_NOARG)
				break;
			/* FALLTHROUGH */
		case OPTION_STRING:
			if (opts->argh) {
				if (opts->flags & PARSE_OPT_OPTARG)
					if (opts->long_name)
						pos += fprintf(stderr, "[=<%s>]", opts->argh);
					else
						pos += fprintf(stderr, "[<%s>]", opts->argh);
				else
					pos += fprintf(stderr, " <%s>", opts->argh);
			} else {
				if (opts->flags & PARSE_OPT_OPTARG)
					if (opts->long_name)
						pos += fprintf(stderr, "[=...]");
					else
						pos += fprintf(stderr, "[...]");
				else
					pos += fprintf(stderr, " ...");
			}
			break;
		default: /* OPTION_{BIT,BOOLEAN,SET_UINT,SET_PTR} */
		case OPTION_END:
		case OPTION_GROUP:
		case OPTION_BIT:
		case OPTION_BOOLEAN:
		case OPTION_INCR:
		case OPTION_SET_UINT:
		case OPTION_SET_PTR:
			break;
		}

		if (pos <= USAGE_OPTS_WIDTH)
			pad = USAGE_OPTS_WIDTH - pos;
		else {
			fputc('\n', stderr);
			pad = USAGE_OPTS_WIDTH;
		}
		fprintf(stderr, "%*s%s\n", pad + USAGE_GAP, "", opts->help);
	}
	fputc('\n', stderr);

	return PARSE_OPT_HELP;
}