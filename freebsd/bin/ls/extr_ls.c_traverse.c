#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int fts_info; char* fts_name; int /*<<< orphan*/  fts_path; int /*<<< orphan*/  fts_level; int /*<<< orphan*/  fts_errno; } ;
typedef  TYPE_1__ FTSENT ;
typedef  int /*<<< orphan*/  FTS ;

/* Variables and functions */
#define  FTS_D 131 
#define  FTS_DC 130 
#define  FTS_DNR 129 
#define  FTS_ERR 128 
 int FTS_NAMEONLY ; 
 int FTS_NOSTAT ; 
 int /*<<< orphan*/  FTS_ROOTLEVEL ; 
 int /*<<< orphan*/  FTS_SKIP ; 
 int /*<<< orphan*/  display (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  f_label ; 
 scalar_t__ f_listdir ; 
 int /*<<< orphan*/  f_listdot ; 
 scalar_t__ f_nosort ; 
 int /*<<< orphan*/  f_recursive ; 
 TYPE_1__* fts_children (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * fts_open (char**,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* fts_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fts_set (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mastercmp ; 
 int output ; 
 int /*<<< orphan*/  printname (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putchar (char) ; 
 int /*<<< orphan*/  puts (char*) ; 
 int rval ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char*,...) ; 

__attribute__((used)) static void
traverse(int argc, char *argv[], int options)
{
	FTS *ftsp;
	FTSENT *p, *chp;
	int ch_options;

	if ((ftsp =
	    fts_open(argv, options, f_nosort ? NULL : mastercmp)) == NULL)
		err(1, "fts_open");

	/*
	 * We ignore errors from fts_children here since they will be
	 * replicated and signalled on the next call to fts_read() below.
	 */
	chp = fts_children(ftsp, 0);
	if (chp != NULL)
		display(NULL, chp, options);
	if (f_listdir)
		return;

	/*
	 * If not recursing down this tree and don't need stat info, just get
	 * the names.
	 */
	ch_options = !f_recursive && !f_label &&
	    options & FTS_NOSTAT ? FTS_NAMEONLY : 0;

	while ((p = fts_read(ftsp)) != NULL)
		switch (p->fts_info) {
		case FTS_DC:
			warnx("%s: directory causes a cycle", p->fts_name);
			break;
		case FTS_DNR:
		case FTS_ERR:
			warnx("%s: %s", p->fts_path, strerror(p->fts_errno));
			rval = 1;
			break;
		case FTS_D:
			if (p->fts_level != FTS_ROOTLEVEL &&
			    p->fts_name[0] == '.' && !f_listdot)
				break;

			/*
			 * If already output something, put out a newline as
			 * a separator.  If multiple arguments, precede each
			 * directory with its name.
			 */
			if (output) {
				putchar('\n');
				(void)printname(p->fts_path);
				puts(":");
			} else if (argc > 1) {
				(void)printname(p->fts_path);
				puts(":");
				output = 1;
			}
			chp = fts_children(ftsp, ch_options);
			display(p, chp, options);

			if (!f_recursive && chp != NULL)
				(void)fts_set(ftsp, p, FTS_SKIP);
			break;
		default:
			break;
		}
	if (errno)
		err(1, "fts_read");
}