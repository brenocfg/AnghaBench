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
struct file_list {char* f_fn; int f_type; struct file_list* f_next; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ EOF ; 
 int atoi (char const*) ; 
 scalar_t__ eq (char*,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* get_word (int /*<<< orphan*/ *) ; 
 scalar_t__ malloc (int) ; 
 char* ns (char const*) ; 
 char* path (char*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* toheader (char const*) ; 
 char* tomacro (char const*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void
do_header(const char *dev, const char *hname, int count)
{
	char *file, *name;
	const char *inw;
	char *inwcopy;
	struct file_list *fl = NULL;	/* may exit for(;;) uninitted */
	struct file_list *fl_head, *fl_prev;
	FILE *inf, *outf;
	int inc, oldcount;

	file = toheader(hname);
	name = tomacro(dev?dev:hname) + (dev == NULL);
	inf = fopen(file, "r");
	oldcount = -1;
	if (inf == 0) {
		(void) unlink(file);
		outf = fopen(file, "w");
		if (outf == 0) {
			perror(file);
			exit(1);
		}
		fprintf(outf, "#define %s %d\n", name, count);
		(void) fclose(outf);
		file = path("meta_features.h");
		outf = fopen(file, "a");
		if (outf == 0) {
			perror(file);
			exit(1);
		}
		fprintf(outf, "#include <%s.h>\n", hname);
		(void) fclose(outf);
		return;
	}
	fl_head = 0;
	for (;;) {
		const char *cp;
		if ((inw = get_word(inf)) == 0 || inw == (char *)EOF)
			break;
		if ((inw = get_word(inf)) == 0 || inw == (char *)EOF)
			break;
		inwcopy = ns(inw);
		cp = get_word(inf);
		if (cp == 0 || cp == (char *)EOF)
			break;
		inc = atoi(cp);
		if (eq(inwcopy, name)) {
			oldcount = inc;
			inc = count;
		}
		cp = get_word(inf);
		if (cp == (char *)EOF)
			break;
		fl = (struct file_list *) malloc(sizeof *fl);
		fl->f_fn = inwcopy;
		fl->f_type = inc;
		fl->f_next = fl_head;
		fl_head = fl;
	}
	(void) fclose(inf);
	if (count == oldcount) {
		while (fl !=0) {
			fl_prev = fl;
			fl = fl->f_next;
			free((char *)fl_prev);
		}
		return;
	}
	if (oldcount == -1) {
		fl = (struct file_list *) malloc(sizeof *fl);
		fl->f_fn = name;
		fl->f_type = count;
		fl->f_next = fl_head;
		fl_head = fl;
	}
	unlink(file);
	outf = fopen(file, "w");
	if (outf == 0) {
		perror(file);
		exit(1);
	}
	for (fl = fl_head; fl != 0; fl = fl->f_next) {
		fprintf(outf, "#define %s %d\n",
		    fl->f_fn, count ? fl->f_type : 0);
		free((char *)fl);
	}
	(void) fclose(outf);
}