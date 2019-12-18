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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
#define  OPTION_HELP 128 
 int STRBUFSZ ; 
 int /*<<< orphan*/  _IOLBF ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stdio () ; 
 char* demangle (char*) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int fgetc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  format ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ isalnum (int) ; 
 int /*<<< orphan*/  longopts ; 
 int noparam ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  putchar (int) ; 
 int /*<<< orphan*/  setvbuf (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strchr (char*,int) ; 
 int stripus ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  version () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char **argv)
{
	char *dem, buf[STRBUFSZ];
	size_t p;
	int c, n, opt;

	while ((opt = getopt_long(argc, argv, "_nps:V", longopts, NULL)) !=
	    -1) {
		switch (opt) {
		case '_':
			stripus = 1;
			break;
		case 'n':
			stripus = 0;
			break;
		case 'p':
			noparam = 1;
			break;
		case 's':
			if ((format = find_format(optarg)) < 0)
				errx(EXIT_FAILURE, "unsupported format: %s",
				    optarg);
			break;
		case 'V':
			version();
			/* NOT REACHED */
		case OPTION_HELP:
		default:
			usage();
			/* NOT REACHED */
		}
	}

	argv += optind;
	argc -= optind;

	if (caph_limit_stdio() < 0)
		err(EXIT_FAILURE, "failed to limit stdio rights");
	if (caph_enter() < 0)
		err(EXIT_FAILURE, "failed to enter capability mode");

	if (*argv != NULL) {
		for (n = 0; n < argc; n++) {
			if ((dem = demangle(argv[n])) == NULL)
				printf("%s\n", argv[n]);
			else
				printf("%s\n", dem);
		}
	} else {
		p = 0;
		for (;;) {
			setvbuf(stdout, NULL, _IOLBF, 0);
			c = fgetc(stdin);
			if (c == EOF || !(isalnum(c) || strchr(".$_", c))) {
				if (p > 0) {
					buf[p] = '\0';
					if ((dem = demangle(buf)) == NULL)
						printf("%s", buf);
					else
						printf("%s", dem);
					p = 0;
				}
				if (c == EOF)
					break;
				putchar(c);
			} else {
				if ((size_t) p >= sizeof(buf) - 1)
					warnx("buffer overflowed");
				else
					buf[p++] = (char) c;
			}

		}
	}

	exit(0);
}