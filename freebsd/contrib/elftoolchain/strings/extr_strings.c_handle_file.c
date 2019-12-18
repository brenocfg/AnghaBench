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
typedef  int /*<<< orphan*/  fileargs_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fileargs_fopen (int /*<<< orphan*/ *,char const*,char*) ; 
 int handle_elf (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warnx (char*,char const*,int /*<<< orphan*/ ) ; 

int
handle_file(fileargs_t *fa, const char *name)
{
	FILE *pfile;
	int rt;

	if (name == NULL)
		return (1);
	pfile = fileargs_fopen(fa, name, "rb");
	if (pfile == NULL) {
		warnx("'%s': %s", name, strerror(errno));
		return (1);
	}

	rt = handle_elf(name, pfile);
	fclose(pfile);
	return (rt);
}