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
struct authuser {char* password; int /*<<< orphan*/ * host; int /*<<< orphan*/ * login; } ;
typedef  int /*<<< orphan*/  line ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* DP ; 
 int /*<<< orphan*/  EX_CONFIG ; 
 int /*<<< orphan*/  EX_NOINPUT ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct authuser*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  authusers ; 
 struct authuser* calloc (int,int) ; 
 int /*<<< orphan*/  chomp (char*) ; 
 int /*<<< orphan*/  errlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errlogx (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 int /*<<< orphan*/  next ; 
 char* strdup (char*) ; 
 void* strsep (char**,char*) ; 

void
parse_authfile(const char *path)
{
	char line[2048];
	struct authuser *au;
	FILE *a;
	char *data;
	int lineno = 0;

	a = fopen(path, "r");
	if (a == NULL) {
		errlog(EX_NOINPUT, "can not open auth file `%s'", path);
		/* NOTREACHED */
	}

	while (!feof(a)) {
		if (fgets(line, sizeof(line), a) == NULL)
			break;
		lineno++;

		chomp(line);

		/* We hit a comment */
		if (*line == '#')
			continue;
		/* Ignore empty lines */
		if (*line == 0)
			continue;

		au = calloc(1, sizeof(*au));
		if (au == NULL)
			errlog(EX_OSERR, "calloc()");

		data = strdup(line);
		au->login = strsep(&data, "|");
		au->host = strsep(&data, DP);
		au->password = data;

		if (au->login == NULL ||
		    au->host == NULL ||
		    au->password == NULL) {
			errlogx(EX_CONFIG, "syntax error in authfile %s:%d", path, lineno);
			/* NOTREACHED */
		}

		SLIST_INSERT_HEAD(&authusers, au, next);
	}

	fclose(a);
}