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
struct stat {int st_size; } ;
struct sec_add {char* name; int size; int /*<<< orphan*/ * content; } ;
struct elfcopy {int /*<<< orphan*/  flags; int /*<<< orphan*/  v_sadd; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SEC_ADD ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct sec_add*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  errx (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 
 scalar_t__ fread (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  sadd_list ; 
 int stat (char const*,struct stat*) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

void
add_section(struct elfcopy *ecp, const char *arg)
{
	struct sec_add	*sa;
	struct stat	 sb;
	const char	*s, *fn;
	FILE		*fp;
	int		 len;

	if ((s = strchr(arg, '=')) == NULL)
		errx(EXIT_FAILURE,
		    "illegal format for --add-section option");
	if ((sa = malloc(sizeof(*sa))) == NULL)
		err(EXIT_FAILURE, "malloc failed");

	len = s - arg;
	if ((sa->name = malloc(len + 1)) == NULL)
		err(EXIT_FAILURE, "malloc failed");
	strncpy(sa->name, arg, len);
	sa->name[len] = '\0';

	fn = s + 1;
	if (stat(fn, &sb) == -1)
		err(EXIT_FAILURE, "stat failed");
	sa->size = sb.st_size;
	if (sa->size > 0) {
		if ((sa->content = malloc(sa->size)) == NULL)
			err(EXIT_FAILURE, "malloc failed");
		if ((fp = fopen(fn, "r")) == NULL)
			err(EXIT_FAILURE, "can not open %s", fn);
		if (fread(sa->content, 1, sa->size, fp) == 0 ||
		    ferror(fp))
			err(EXIT_FAILURE, "fread failed");
		fclose(fp);
	} else
		sa->content = NULL;

	STAILQ_INSERT_TAIL(&ecp->v_sadd, sa, sadd_list);
	ecp->flags |= SEC_ADD;
}