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

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char) ; 
 int getopt (int,char**,char const*) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  stderr ; 
 char* strchr (char const*,char) ; 

int
getoldopt(int argc, char **argv, const char *optstring)
{
	static char	*key;		/* Points to next keyletter */
	static char	use_getopt;	/* !=0 if argv[1][0] was '-' */
	char		c;
	char		*place;

	optarg = NULL;

	if (key == NULL) {		/* First time */
		if (argc < 2)
			return (-1);
		key = argv[1];
		if (*key == '-')
			use_getopt++;
		else
			optind = 2;
	}

	if (use_getopt)
		return (getopt(argc, argv, optstring));

	c = *key++;
	if (c == '\0') {
		key--;
		return (-1);
	}
	place = strchr(optstring, c);

	if (place == NULL || c == ':') {
		fprintf(stderr, "%s: unknown option %c\n", argv[0], c);
		return ('?');
	}

	place++;
	if (*place == ':') {
		if (optind < argc) {
			optarg = argv[optind];
			optind++;
		} else {
			fprintf(stderr, "%s: %c argument missing\n",
				argv[0], c);
			return ('?');
		}
	}

	return (c);
}