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
struct Scsi_Host {scalar_t__ hostdata; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int /*<<< orphan*/  ips_ha_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int ips_host_info (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int ips_next_controller ; 
 struct Scsi_Host** ips_sh ; 

__attribute__((used)) static int
ips_proc_info(struct Scsi_Host *host, char *buffer, char **start, off_t offset,
	      int length, int func)
{
	int i;
	int ret;
	ips_ha_t *ha = NULL;

	METHOD_TRACE("ips_proc_info", 1);

	/* Find our host structure */
	for (i = 0; i < ips_next_controller; i++) {
		if (ips_sh[i]) {
			if (ips_sh[i] == host) {
				ha = (ips_ha_t *) ips_sh[i]->hostdata;
				break;
			}
		}
	}

	if (!ha)
		return (-EINVAL);

	if (func) {
		/* write */
		return (0);
	} else {
		/* read */
		if (start)
			*start = buffer;

		ret = ips_host_info(ha, buffer, offset, length);

		return (ret);
	}
}