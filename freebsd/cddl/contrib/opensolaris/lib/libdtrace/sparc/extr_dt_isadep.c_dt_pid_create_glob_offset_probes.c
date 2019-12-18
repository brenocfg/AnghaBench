#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ulong_t ;
struct ps_prochandle {int dummy; } ;
typedef  int /*<<< orphan*/  i ;
struct TYPE_9__ {uintptr_t ftps_pc; size_t ftps_size; int ftps_noffs; scalar_t__* ftps_offs; int /*<<< orphan*/  ftps_type; } ;
typedef  TYPE_1__ fasttrap_probe_spec_t ;
struct TYPE_10__ {int /*<<< orphan*/  dt_ftfd; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_11__ {scalar_t__ st_size; scalar_t__ st_value; } ;
typedef  TYPE_3__ GElf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  DTFTP_OFFSETS ; 
 int /*<<< orphan*/  FASTTRAPIOC_MAKEPROBE ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ ) ; 
 int dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ gmatch (char*,char const*) ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,scalar_t__) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
dt_pid_create_glob_offset_probes(struct ps_prochandle *P, dtrace_hdl_t *dtp,
    fasttrap_probe_spec_t *ftp, const GElf_Sym *symp, const char *pattern)
{
	ulong_t i;

	ftp->ftps_type = DTFTP_OFFSETS;
	ftp->ftps_pc = (uintptr_t)symp->st_value;
	ftp->ftps_size = (size_t)symp->st_size;
	ftp->ftps_noffs = 0;

	/*
	 * If we're matching against everything, just iterate through each
	 * instruction in the function, otherwise look for matching offset
	 * names by constructing the string and comparing it against the
	 * pattern.
	 */
	if (strcmp("*", pattern) == 0) {
		for (i = 0; i < symp->st_size; i += 4) {
			ftp->ftps_offs[ftp->ftps_noffs++] = i;
		}
	} else {
		char name[sizeof (i) * 2 + 1];

		for (i = 0; i < symp->st_size; i += 4) {
			(void) sprintf(name, "%lx", i);
			if (gmatch(name, pattern))
				ftp->ftps_offs[ftp->ftps_noffs++] = i;
		}
	}

	if (ioctl(dtp->dt_ftfd, FASTTRAPIOC_MAKEPROBE, ftp) != 0) {
		dt_dprintf("fasttrap probe creation ioctl failed: %s\n",
		    strerror(errno));
		return (dt_set_errno(dtp, errno));
	}

	return (ftp->ftps_noffs);
}