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
typedef  int /*<<< orphan*/  dtrace_prog_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_2__ {int dofh_loadsz; } ;
typedef  TYPE_1__ dof_hdr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DTRACE_VERSION ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  bcopy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  corrupt (int,unsigned char*,int) ; 
 unsigned char* dtrace_dof_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errmsg (int /*<<< orphan*/ *,int) ; 
 int dtrace_errno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dtrace_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/ * dtrace_program_fcompile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*,...) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 unsigned char* malloc (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

int
main(int argc, char **argv)
{
	char *filename = argv[1];
	dtrace_hdl_t *dtp;
	dtrace_prog_t *pgp;
	int err, fd, len;
	FILE *fp;
	unsigned char *dof, *copy;

	if (argc < 2)
		fatal("expected D script as argument\n");

	if ((fp = fopen(filename, "r")) == NULL)
		fatal("couldn't open %s", filename);

	/*
	 * First, we need to compile our provided D into DOF.
	 */
	if ((dtp = dtrace_open(DTRACE_VERSION, 0, &err)) == NULL) {
		fatal("cannot open dtrace library: %s\n",
		    dtrace_errmsg(NULL, err));
	}

	pgp = dtrace_program_fcompile(dtp, fp, 0, 0, NULL);
	fclose(fp);

	if (pgp == NULL) {
		fatal("failed to compile script %s: %s\n", filename,
		    dtrace_errmsg(dtp, dtrace_errno(dtp)));
	}

	dof = dtrace_dof_create(dtp, pgp, 0);
	len = ((dof_hdr_t *)dof)->dofh_loadsz;

	if ((copy = malloc(len)) == NULL)
		fatal("could not allocate copy of %d bytes", len);

	for (;;) {
		bcopy(dof, copy, len);
		/*
		 * Open another instance of the dtrace device.
		 */
		fd = open("/devices/pseudo/dtrace@0:dtrace", O_RDWR);

		if (fd == -1)
			fatal("couldn't open DTrace pseudo device");

		corrupt(fd, copy, len);
		close(fd);
	}

	/* NOTREACHED */
	return (0);
}