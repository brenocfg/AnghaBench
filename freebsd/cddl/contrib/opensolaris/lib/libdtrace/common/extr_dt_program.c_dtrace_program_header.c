#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  dt_provlist; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_provider_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  dt_header_fmt_macro (char*,char const*) ; 
 scalar_t__ dt_header_provider (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dt_list_next (int /*<<< orphan*/ *) ; 
 int dt_set_errno (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ strlen (char const*) ; 
 char* strrchr (char const*,char) ; 

int
dtrace_program_header(dtrace_hdl_t *dtp, FILE *out, const char *fname)
{
	dt_provider_t *pvp;
	char *mfname, *p;

	if (fname != NULL) {
		if ((p = strrchr(fname, '/')) != NULL)
			fname = p + 1;

		mfname = alloca(strlen(fname) + 1);
		dt_header_fmt_macro(mfname, fname);
		if (fprintf(out, "#ifndef\t_%s\n#define\t_%s\n\n",
		    mfname, mfname) < 0)
			return (dt_set_errno(dtp, errno));
	}

	if (fprintf(out, "#include <unistd.h>\n\n") < 0)
		return (-1);

	if (fprintf(out, "#ifdef\t__cplusplus\nextern \"C\" {\n#endif\n\n") < 0)
		return (-1);

	for (pvp = dt_list_next(&dtp->dt_provlist);
	    pvp != NULL; pvp = dt_list_next(pvp)) {
		if (dt_header_provider(dtp, pvp, out) != 0)
			return (-1); /* dt_errno is set for us */
	}

	if (fprintf(out, "\n#ifdef\t__cplusplus\n}\n#endif\n") < 0)
		return (dt_set_errno(dtp, errno));

	if (fname != NULL && fprintf(out, "\n#endif\t/* _%s */\n", mfname) < 0)
		return (dt_set_errno(dtp, errno));

	return (0);
}