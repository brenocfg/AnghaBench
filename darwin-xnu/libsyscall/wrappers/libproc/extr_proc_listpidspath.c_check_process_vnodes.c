#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vpi ;
struct TYPE_5__ {int /*<<< orphan*/  vi_stat; } ;
struct TYPE_6__ {TYPE_1__ vip_vi; } ;
struct TYPE_8__ {int /*<<< orphan*/  vi_stat; } ;
struct TYPE_7__ {TYPE_4__ vip_vi; } ;
struct proc_vnodepathinfo {TYPE_2__ pvi_rdir; TYPE_3__ pvi_cdir; } ;
typedef  int /*<<< orphan*/  fdOpenInfoRef ;

/* Variables and functions */
 scalar_t__ ESRCH ; 
 int /*<<< orphan*/  PROC_PIDVNODEPATHINFO ; 
 int check_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int proc_pidinfo (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc_vnodepathinfo*,int) ; 

__attribute__((used)) static int
check_process_vnodes(fdOpenInfoRef info, int pid)
{
	int				buf_used;
	int				status;
	struct proc_vnodepathinfo	vpi;

	buf_used = proc_pidinfo(pid, PROC_PIDVNODEPATHINFO, 0, &vpi, sizeof(vpi));
	if (buf_used <= 0) {
		if (errno == ESRCH) {
			// if the process is gone
			return 0;
		}
		return -1;
	} else if (buf_used < sizeof(vpi)) {
		// if we didn't get enough information
		return -1;
	}

	// processing current working directory
	status = check_file(info, &vpi.pvi_cdir.vip_vi.vi_stat);
	if (status != 0) {
		// if error or match
		return status;
	}

	// processing root directory
	status = check_file(info, &vpi.pvi_rdir.vip_vi.vi_stat);
	if (status != 0) {
		// if error or match
		return status;
	}

	return 0;
}