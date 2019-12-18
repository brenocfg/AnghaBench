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
 scalar_t__ MAP_FAILED ; 
 int /*<<< orphan*/  MAP_PRIVATE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  PROT_READ ; 
 scalar_t__ close (int) ; 
 int errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  filesize ; 
 int firstloc ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_filesize (int) ; 
 int /*<<< orphan*/  get_pattern (int,char**) ; 
 int inputfd ; 
 char* inputname ; 
 scalar_t__ madr ; 
 scalar_t__ mmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ munmap (scalar_t__,int /*<<< orphan*/ ) ; 
 int num_matches ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 char* progname ; 
 int /*<<< orphan*/  search_pattern () ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  usage () ; 

int main (int argc, char *argv [])
{
	progname = argv[0];

	if (argc < 3)
		usage ();

	get_pattern (argc - 2, argv + 2);

	inputname = argv[1];

	inputfd = open (inputname, O_RDONLY);
	if (inputfd == -1) {
		fprintf (stderr, "%s: cannot open '%s'\n",
				progname, inputname);
		exit (3);
	}

	filesize = get_filesize (inputfd);

	madr = mmap (0, filesize, PROT_READ, MAP_PRIVATE, inputfd, 0);
	if (madr == MAP_FAILED) {
		fprintf (stderr, "mmap error = %d\n", errno);
		close (inputfd);
		exit (4);
	}

	search_pattern ();

	if (munmap (madr, filesize))
		fprintf (stderr, "munmap error = %d\n", errno);

	if (close (inputfd))
		fprintf (stderr, "%s: error %d closing '%s'\n",
				progname, errno, inputname);

	fprintf (stderr, "number of pattern matches = %d\n", num_matches);
	if (num_matches == 0)
		firstloc = ~0;
	printf ("%ld\n", firstloc);
	fprintf (stderr, "%ld\n", firstloc);

	exit (num_matches ? 0 : 2);
}