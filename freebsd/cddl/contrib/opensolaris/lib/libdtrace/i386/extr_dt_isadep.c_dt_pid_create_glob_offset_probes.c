#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_13__ ;

/* Type definitions */
typedef  int ulong_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct ps_prochandle {int dummy; } ;
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  i ;
struct TYPE_15__ {uintptr_t ftps_pc; size_t ftps_size; scalar_t__ ftps_noffs; int* ftps_offs; int /*<<< orphan*/  ftps_type; } ;
typedef  TYPE_1__ fasttrap_probe_spec_t ;
struct TYPE_16__ {int /*<<< orphan*/  dt_ftfd; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_17__ {int st_size; int st_value; } ;
struct TYPE_14__ {char pr_dmodel; int /*<<< orphan*/  pr_pid; } ;
typedef  TYPE_3__ GElf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  DTFTP_OFFSETS ; 
 int DT_PROC_ERR ; 
 int /*<<< orphan*/  FASTTRAPIOC_MAKEPROBE ; 
 int Pread (struct ps_prochandle*,int /*<<< orphan*/ *,int,int) ; 
 TYPE_13__* Pstatus (struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_dprintf (char*,...) ; 
 int dt_instr_size (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int,char) ; 
 scalar_t__ dt_pid_has_jump_table (struct ps_prochandle*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*) ; 
 int dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ gmatch (char*,char const*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 char proc_getmodel (struct ps_prochandle*) ; 
 int /*<<< orphan*/  proc_getpid (struct ps_prochandle*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
dt_pid_create_glob_offset_probes(struct ps_prochandle *P, dtrace_hdl_t *dtp,
    fasttrap_probe_spec_t *ftp, const GElf_Sym *symp, const char *pattern)
{
	uint8_t *text;
	int size;
	ulong_t i, end = symp->st_size;
#ifdef illumos
	pid_t pid = Pstatus(P)->pr_pid;
	char dmodel = Pstatus(P)->pr_dmodel;
#else
	pid_t pid = proc_getpid(P);
	char dmodel = proc_getmodel(P);
#endif

	ftp->ftps_type = DTFTP_OFFSETS;
	ftp->ftps_pc = (uintptr_t)symp->st_value;
	ftp->ftps_size = (size_t)symp->st_size;
	ftp->ftps_noffs = 0;

	if ((text = malloc(symp->st_size)) == NULL) {
		dt_dprintf("mr sparkle: malloc() failed\n");
		return (DT_PROC_ERR);
	}

	if (Pread(P, text, symp->st_size, symp->st_value) != symp->st_size) {
		dt_dprintf("mr sparkle: Pread() failed\n");
		free(text);
		return (DT_PROC_ERR);
	}

	/*
	 * We can't instrument offsets in functions with jump tables as
	 * we might interpret a jump table offset as an instruction.
	 */
	if (dt_pid_has_jump_table(P, dtp, text, ftp, symp)) {
		free(text);
		return (0);
	}

	if (strcmp("*", pattern) == 0) {
		for (i = 0; i < end; i += size) {
			ftp->ftps_offs[ftp->ftps_noffs++] = i;

			size = dt_instr_size(&text[i], dtp, pid,
			    symp->st_value + i, dmodel);

			/* bail if we hit an invalid opcode */
			if (size <= 0)
				break;
		}
	} else {
		char name[sizeof (i) * 2 + 1];

		for (i = 0; i < end; i += size) {
			(void) snprintf(name, sizeof (name), "%lx", i);
			if (gmatch(name, pattern))
				ftp->ftps_offs[ftp->ftps_noffs++] = i;

			size = dt_instr_size(&text[i], dtp, pid,
			    symp->st_value + i, dmodel);

			/* bail if we hit an invalid opcode */
			if (size <= 0)
				break;
		}
	}

	free(text);
	if (ftp->ftps_noffs > 0) {
		if (ioctl(dtp->dt_ftfd, FASTTRAPIOC_MAKEPROBE, ftp) != 0) {
			dt_dprintf("fasttrap probe creation ioctl failed: %s\n",
			    strerror(errno));
			return (dt_set_errno(dtp, errno));
		}
	}

	return (ftp->ftps_noffs);
}