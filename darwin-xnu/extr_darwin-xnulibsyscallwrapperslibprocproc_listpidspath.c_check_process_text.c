#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_11__ {scalar_t__ pri_size; scalar_t__ pri_address; } ;
struct TYPE_9__ {int /*<<< orphan*/  vi_stat; } ;
struct TYPE_10__ {TYPE_2__ vip_vi; } ;
struct proc_regionwithpathinfo {TYPE_4__ prp_prinfo; TYPE_3__ prp_vip; } ;
typedef  int /*<<< orphan*/  rwpi ;
typedef  TYPE_5__* fdOpenInfoRef ;
struct TYPE_8__ {scalar_t__ st_dev; } ;
struct TYPE_12__ {int flags; TYPE_1__ match_stat; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 scalar_t__ ESRCH ; 
 int PROC_LISTPIDSPATH_PATH_IS_VOLUME ; 
 int /*<<< orphan*/  PROC_PIDREGIONPATHINFO2 ; 
 int /*<<< orphan*/  PROC_PIDREGIONPATHINFO3 ; 
 int check_file (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int proc_pidinfo (int,int /*<<< orphan*/ ,scalar_t__,struct proc_regionwithpathinfo*,int) ; 

__attribute__((used)) static int
check_process_text(fdOpenInfoRef info, int pid)
{
	int		status;
	int		buf_used;
	struct proc_regionwithpathinfo	rwpi;

	if (info->flags & PROC_LISTPIDSPATH_PATH_IS_VOLUME) {

		// ask for first memory region that matches mountpoint
		buf_used = proc_pidinfo(pid, PROC_PIDREGIONPATHINFO3, info->match_stat.st_dev, &rwpi, sizeof(rwpi));
		if (buf_used <= 0) {
			if ((errno == ESRCH) || (errno == EINVAL)) {
				// if no more text information is available for this process.
				return 0;
			}
			return -1;
		} else if (buf_used < sizeof(rwpi)) {
			// if we didn't get enough information
			return -1;
		}
		
		status = check_file(info, &rwpi.prp_vip.vip_vi.vi_stat);
		if (status != 0) {
			// if error or match
			return status;
		}
	} else {
		uint64_t	a	= 0;
		
		while (1) {	// for all memory regions
			// processing next address
			buf_used = proc_pidinfo(pid, PROC_PIDREGIONPATHINFO2, a, &rwpi, sizeof(rwpi));
			if (buf_used <= 0) {
				if ((errno == ESRCH) || (errno == EINVAL)) {
					// if no more text information is available for this process.
					break;
				}
				return -1;
			} else if (buf_used < sizeof(rwpi)) {
				// if we didn't get enough information
				return -1;
			}
			
			status = check_file(info, &rwpi.prp_vip.vip_vi.vi_stat);
			if (status != 0) {
				// if error or match
				return status;
			}
			
			a = rwpi.prp_prinfo.pri_address + rwpi.prp_prinfo.pri_size;
		}
	}

	return 0;
}