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
typedef  int /*<<< orphan*/  time_t ;
typedef  int /*<<< orphan*/  rcc_program_ty ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  _O_BINARY ; 
 int /*<<< orphan*/  _fileno (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _setmode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 float assert (int) ; 
 char* ctime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_program (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int /*<<< orphan*/ * freopen (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rcc_read_program (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcsid ; 
 int read_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdin ; 
 int /*<<< orphan*/  stdout ; 
 scalar_t__ strcmp (char*,char*) ; 
 int strstr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strtod (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[]) {
	int i, version;
	float stamp = (assert(strstr(rcsid, ",v")), strtod(strstr(rcsid, ",v")+2, NULL))
;
	char *infile = NULL, *outfile = NULL;
	rcc_program_ty pickle;

	for (i = 1; i < argc; i++)
		if (*argv[i] != '-' || strcmp(argv[i], "-") == 0) {
			if (infile == NULL)
				infile = argv[i];
			else if (outfile == NULL)
				outfile = argv[i];
		}
	if (infile != NULL && strcmp(infile, "-") != 0
	&& freopen(infile, "rb", stdin) == NULL) {
		fprintf(stderr, "%s: can't read `%s'\n", argv[0], infile);
		exit(EXIT_FAILURE);
	}
	if (infile == NULL || strcmp(infile, "-") == 0)
		infile = "Standard Input";
#if WIN32
	else
		_setmode(_fileno(stdin), _O_BINARY);
#endif
	if (outfile != NULL && strcmp(outfile, "-") != 0
	&& freopen(outfile, "w", stdout) == NULL) {
		fprintf(stderr, "%s: can't write `%s'\n", argv[0], outfile);
		exit(EXIT_FAILURE);
	}
	version = read_int(stdin);
	assert(version/100 == (int)stamp);
	pickle = rcc_read_program(stdin);
	printf("<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\"\n");
	printf("<html><head><title>%s</title>\n"
	"<link rev=made href=\"mailto:drh@microsoft.com\">\n"
	"</head><body>\n<h1>%s</h1>\n",	infile, infile);
	printf("<p>version = %d.%d</p>", version/100, version%100);
	do_program(pickle);
	{
		time_t t;
		time(&t);
		printf("<hr><address>%s</address>\n", ctime(&t));
	}
	printf("</body></html>\n");
	return EXIT_SUCCESS;
}