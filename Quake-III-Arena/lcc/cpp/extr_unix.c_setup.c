#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar ;
typedef  int /*<<< orphan*/  Tokenrow ;
struct TYPE_2__ {int always; int deleted; char* file; } ;

/* Variables and functions */
 int /*<<< orphan*/  Cplusplus ; 
 int /*<<< orphan*/  FATAL ; 
 scalar_t__ Mflag ; 
 int NINCLUDE ; 
 int creat (char*,int) ; 
 int /*<<< orphan*/  doadefine (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dup2 (int,int) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  gettokens (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* includelist ; 
 int /*<<< orphan*/  maketokenrow (int,int /*<<< orphan*/ *) ; 
 scalar_t__ newstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 char* optarg ; 
 int optind ; 
 char* rcsid ; 
 int /*<<< orphan*/  setobjname (char*) ; 
 int /*<<< orphan*/  setsource (char*,int,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int /*<<< orphan*/  unsetsource () ; 
 int /*<<< orphan*/  verbose ; 

void
setup(int argc, char **argv)
{
	int c, fd, i;
	char *fp, *dp;
	Tokenrow tr;
	extern void setup_kwtab(void);

	setup_kwtab();
	while ((c = getopt(argc, argv, "MNOVv+I:D:U:F:lg")) != -1)
		switch (c) {
		case 'N':
			for (i=0; i<NINCLUDE; i++)
				if (includelist[i].always==1)
					includelist[i].deleted = 1;
			break;
		case 'I':
			for (i=NINCLUDE-2; i>=0; i--) {
				if (includelist[i].file==NULL) {
					includelist[i].always = 1;
					includelist[i].file = optarg;
					break;
				}
			}
			if (i<0)
				error(FATAL, "Too many -I directives");
			break;
		case 'D':
		case 'U':
			setsource("<cmdarg>", -1, optarg);
			maketokenrow(3, &tr);
			gettokens(&tr, 1);
			doadefine(&tr, c);
			unsetsource();
			break;
		case 'M':
			Mflag++;
			break;
		case 'v':
			fprintf(stderr, "%s %s\n", argv[0], rcsid);
			break;
		case 'V':
			verbose++;
			break;
		case '+':
			Cplusplus++;
			break;
		default:
			break;
		}
	dp = ".";
	fp = "<stdin>";
	fd = 0;
	if (optind<argc) {
		if ((fp = strrchr(argv[optind], '/')) != NULL) {
			int len = fp - argv[optind];
			dp = (char*)newstring((uchar*)argv[optind], len+1, 0);
			dp[len] = '\0';
		}
		fp = (char*)newstring((uchar*)argv[optind], strlen(argv[optind]), 0);
		if ((fd = open(fp, 0)) <= 0)
			error(FATAL, "Can't open input file %s", fp);
	}
	if (optind+1<argc) {
		int fdo = creat(argv[optind+1], 0666);
		if (fdo<0)
			error(FATAL, "Can't open output file %s", argv[optind+1]);
		dup2(fdo, 1);
	}
	if(Mflag)
		setobjname(fp);
	includelist[NINCLUDE-1].always = 0;
	includelist[NINCLUDE-1].file = dp;
	setsource(fp, fd, NULL);
}