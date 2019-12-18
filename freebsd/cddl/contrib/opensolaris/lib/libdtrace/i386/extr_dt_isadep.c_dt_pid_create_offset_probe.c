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
struct TYPE_15__ {uintptr_t ftps_pc; size_t ftps_size; int ftps_noffs; int* ftps_offs; int /*<<< orphan*/  ftps_func; int /*<<< orphan*/  ftps_type; } ;
typedef  TYPE_1__ fasttrap_probe_spec_t ;
struct TYPE_16__ {int /*<<< orphan*/  dt_ftfd; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_17__ {scalar_t__ st_size; scalar_t__ st_value; } ;
struct TYPE_14__ {char pr_dmodel; int /*<<< orphan*/  pr_pid; } ;
typedef  TYPE_3__ GElf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  DTFTP_OFFSETS ; 
 int DT_PROC_ALIGN ; 
 int DT_PROC_ERR ; 
 int /*<<< orphan*/  FASTTRAPIOC_MAKEPROBE ; 
 scalar_t__ Pread (struct ps_prochandle*,int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 TYPE_13__* Pstatus (struct ps_prochandle*) ; 
 int /*<<< orphan*/  dt_dprintf (char*,...) ; 
 int dt_instr_size (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,scalar_t__,char) ; 
 scalar_t__ dt_pid_has_jump_table (struct ps_prochandle*,TYPE_2__*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_3__ const*) ; 
 int dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (scalar_t__) ; 
 char proc_getmodel (struct ps_prochandle*) ; 
 int /*<<< orphan*/  proc_getpid (struct ps_prochandle*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
dt_pid_create_offset_probe(struct ps_prochandle *P, dtrace_hdl_t *dtp,
    fasttrap_probe_spec_t *ftp, const GElf_Sym *symp, ulong_t off)
{
	ftp->ftps_type = DTFTP_OFFSETS;
	ftp->ftps_pc = (uintptr_t)symp->st_value;
	ftp->ftps_size = (size_t)symp->st_size;
	ftp->ftps_noffs = 1;

	if (strcmp("-", ftp->ftps_func) == 0) {
		ftp->ftps_offs[0] = off;
	} else {
		uint8_t *text;
		ulong_t i;
		int size;
#ifdef illumos
		pid_t pid = Pstatus(P)->pr_pid;
		char dmodel = Pstatus(P)->pr_dmodel;
#else
		pid_t pid = proc_getpid(P);
		char dmodel = proc_getmodel(P);
#endif

		if ((text = malloc(symp->st_size)) == NULL) {
			dt_dprintf("mr sparkle: malloc() failed\n");
			return (DT_PROC_ERR);
		}

		if (Pread(P, text, symp->st_size, symp->st_value) !=
		    symp->st_size) {
			dt_dprintf("mr sparkle: Pread() failed\n");
			free(text);
			return (DT_PROC_ERR);
		}

		/*
		 * We can't instrument offsets in functions with jump tables
		 * as we might interpret a jump table offset as an
		 * instruction.
		 */
		if (dt_pid_has_jump_table(P, dtp, text, ftp, symp)) {
			free(text);
			return (0);
		}

		for (i = 0; i < symp->st_size; i += size) {
			if (i == off) {
				ftp->ftps_offs[0] = i;
				break;
			}

			/*
			 * If we've passed the desired offset without a
			 * match, then the given offset must not lie on a
			 * instruction boundary.
			 */
			if (i > off) {
				free(text);
				return (DT_PROC_ALIGN);
			}

			size = dt_instr_size(&text[i], dtp, pid,
			    symp->st_value + i, dmodel);

			/*
			 * If we hit an invalid instruction, bail as if we
			 * couldn't find the offset.
			 */
			if (size <= 0) {
				free(text);
				return (DT_PROC_ALIGN);
			}
		}

		free(text);
	}

	if (ioctl(dtp->dt_ftfd, FASTTRAPIOC_MAKEPROBE, ftp) != 0) {
		dt_dprintf("fasttrap probe creation ioctl failed: %s\n",
		    strerror(errno));
		return (dt_set_errno(dtp, errno));
	}

	return (ftp->ftps_noffs);
}