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
struct ps_prochandle {int dummy; } ;
struct TYPE_9__ {uintptr_t ftps_pc; size_t ftps_size; int ftps_noffs; scalar_t__* ftps_offs; int /*<<< orphan*/  ftps_type; } ;
typedef  TYPE_1__ fasttrap_probe_spec_t ;
struct TYPE_10__ {int /*<<< orphan*/  dt_ftfd; } ;
typedef  TYPE_2__ dtrace_hdl_t ;
struct TYPE_11__ {scalar_t__ st_size; scalar_t__ st_value; } ;
typedef  TYPE_3__ GElf_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  DTFTP_ENTRY ; 
 int /*<<< orphan*/  FASTTRAPIOC_MAKEPROBE ; 
 int /*<<< orphan*/  dt_dprintf (char*,int /*<<< orphan*/ ) ; 
 int dt_set_errno (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
dt_pid_create_entry_probe(struct ps_prochandle *P, dtrace_hdl_t *dtp,
    fasttrap_probe_spec_t *ftp, const GElf_Sym *symp)
{
	ftp->ftps_type = DTFTP_ENTRY;
	ftp->ftps_pc = (uintptr_t)symp->st_value;
	ftp->ftps_size = (size_t)symp->st_size;
	ftp->ftps_noffs = 1;
	ftp->ftps_offs[0] = 0;

	if (ioctl(dtp->dt_ftfd, FASTTRAPIOC_MAKEPROBE, ftp) != 0) {
		dt_dprintf("fasttrap probe creation ioctl failed: %s\n",
		    strerror(errno));
		return (dt_set_errno(dtp, errno));
	}

	return (1);
}