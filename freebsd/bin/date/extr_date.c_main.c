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
struct vary {char* arg; } ;
struct tm {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_sec; } ;
struct stat {TYPE_1__ st_mtim; } ;
typedef  int /*<<< orphan*/  buf ;
struct TYPE_6__ {int /*<<< orphan*/  refname; } ;

/* Variables and functions */
 int /*<<< orphan*/  LC_TIME ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 TYPE_2__* iso8601_fmts ; 
 TYPE_2__* iso8601_selected ; 
 int /*<<< orphan*/  iso8601_usage (char*) ; 
 struct tm* localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  multipleformats () ; 
 size_t nitems (TYPE_2__*) ; 
 char* optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printdate (char*) ; 
 int /*<<< orphan*/  printisodate (struct tm*) ; 
 char const* rfc2822_format ; 
 int /*<<< orphan*/  setenv (char*,char*,int) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setthetime (char*,char*,int) ; 
 int /*<<< orphan*/  stat (char*,struct stat*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strftime (char*,int,char const*,struct tm*) ; 
 int /*<<< orphan*/  strtoq (char*,char**,int /*<<< orphan*/ ) ; 
 int time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tval ; 
 int /*<<< orphan*/  usage () ; 
 struct vary* vary_append (struct vary*,char*) ; 
 struct vary* vary_apply (struct vary*,struct tm*) ; 
 int /*<<< orphan*/  vary_destroy (struct vary*) ; 

int
main(int argc, char *argv[])
{
	int ch, rflag;
	bool Iflag, jflag, Rflag;
	const char *format;
	char buf[1024];
	char *fmt;
	char *tmp;
	struct vary *v;
	const struct vary *badv;
	struct tm *lt;
	struct stat sb;
	size_t i;

	v = NULL;
	fmt = NULL;
	(void) setlocale(LC_TIME, "");
	rflag = 0;
	Iflag = jflag = Rflag = 0;
	while ((ch = getopt(argc, argv, "f:I::jnRr:uv:")) != -1)
		switch((char)ch) {
		case 'f':
			fmt = optarg;
			break;
		case 'I':
			if (Rflag)
				multipleformats();
			Iflag = 1;
			if (optarg == NULL) {
				iso8601_selected = iso8601_fmts;
				break;
			}
			for (i = 0; i < nitems(iso8601_fmts); i++)
				if (strcmp(optarg, iso8601_fmts[i].refname) == 0)
					break;
			if (i == nitems(iso8601_fmts))
				iso8601_usage(optarg);

			iso8601_selected = &iso8601_fmts[i];
			break;
		case 'j':
			jflag = 1;	/* don't set time */
			break;
		case 'n':
			break;
		case 'R':		/* RFC 2822 datetime format */
			if (Iflag)
				multipleformats();
			Rflag = 1;
			break;
		case 'r':		/* user specified seconds */
			rflag = 1;
			tval = strtoq(optarg, &tmp, 0);
			if (*tmp != 0) {
				if (stat(optarg, &sb) == 0)
					tval = sb.st_mtim.tv_sec;
				else
					usage();
			}
			break;
		case 'u':		/* do everything in UTC */
			(void)setenv("TZ", "UTC0", 1);
			break;
		case 'v':
			v = vary_append(v, optarg);
			break;
		default:
			usage();
		}
	argc -= optind;
	argv += optind;

	if (!rflag && time(&tval) == -1)
		err(1, "time");

	format = "%+";

	if (Rflag)
		format = rfc2822_format;

	/* allow the operands in any order */
	if (*argv && **argv == '+') {
		if (Iflag)
			multipleformats();
		format = *argv + 1;
		++argv;
	}

	if (*argv) {
		setthetime(fmt, *argv, jflag);
		++argv;
	} else if (fmt != NULL)
		usage();

	if (*argv && **argv == '+') {
		if (Iflag)
			multipleformats();
		format = *argv + 1;
	}

	lt = localtime(&tval);
	if (lt == NULL)
		errx(1, "invalid time");
	badv = vary_apply(v, lt);
	if (badv) {
		fprintf(stderr, "%s: Cannot apply date adjustment\n",
			badv->arg);
		vary_destroy(v);
		usage();
	}
	vary_destroy(v);

	if (Iflag)
		printisodate(lt);

	if (format == rfc2822_format)
		/*
		 * When using RFC 2822 datetime format, don't honor the
		 * locale.
		 */
		setlocale(LC_TIME, "C");

	(void)strftime(buf, sizeof(buf), format, lt);
	printdate(buf);
}