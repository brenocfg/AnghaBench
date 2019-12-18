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
typedef  char uuid_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  caph_cache_catpages () ; 
 scalar_t__ caph_enter () ; 
 scalar_t__ caph_limit_stdio () ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  errx (int,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getopt (int,char**,char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  optarg ; 
 scalar_t__ optind ; 
 int /*<<< orphan*/ * stdout ; 
 int strtol (int /*<<< orphan*/ ,char**,int) ; 
 int /*<<< orphan*/  usage () ; 
 int uuid_s_ok ; 
 int /*<<< orphan*/  uuid_to_string (int /*<<< orphan*/ ,char**,int*) ; 
 scalar_t__ uuidgen (char*,int) ; 

int
main(int argc, char *argv[])
{
	FILE *fp;
	uuid_t *store, *uuid;
	char *p;
	int ch, count, i, iterate, status;

	count = -1;	/* no count yet */
	fp = stdout;	/* default output file */
	iterate = 0;	/* not one at a time */
	while ((ch = getopt(argc, argv, "1n:o:")) != -1)
		switch (ch) {
		case '1':
			iterate = 1;
			break;
		case 'n':
			if (count > 0)
				usage();
			count = strtol(optarg, &p, 10);
			if (*p != 0 || count < 1)
				usage();
			break;
		case 'o':
			if (fp != stdout)
				errx(1, "multiple output files not allowed");
			fp = fopen(optarg, "w");
			if (fp == NULL)
				err(1, "fopen");
			break;
		default:
			usage();
		}
	argv += optind;
	argc -= optind;

	if (argc)
		usage();

	caph_cache_catpages();
	if (caph_limit_stdio() < 0)
		err(1, "Unable to limit stdio");
	if (caph_enter() < 0)
		err(1, "Unable to enter capability mode");

	if (count == -1)
		count = 1;

	store = (uuid_t*)malloc(sizeof(uuid_t) * count);
	if (store == NULL)
		err(1, "malloc()");

	if (!iterate) {
		/* Get them all in a single batch */
		if (uuidgen(store, count) != 0)
			err(1, "uuidgen()");
	} else {
		uuid = store;
		for (i = 0; i < count; i++) {
			if (uuidgen(uuid++, 1) != 0)
				err(1, "uuidgen()");
		}
	}

	uuid = store;
	while (count--) {
		uuid_to_string(uuid++, &p, &status);
		if (status != uuid_s_ok)
		     err(1, "cannot stringify a UUID");
		fprintf(fp, "%s\n", p);
		free(p);
	}

	free(store);
	if (fp != stdout)
		fclose(fp);
	return (0);
}