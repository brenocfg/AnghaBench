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
struct sysdev_class {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {scalar_t__ ctnid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODATA ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long long) ; 
 TYPE_1__ stp_info ; 
 int /*<<< orphan*/  stp_online ; 

__attribute__((used)) static ssize_t stp_ctn_id_show(struct sysdev_class *class, char *buf)
{
	if (!stp_online)
		return -ENODATA;
	return sprintf(buf, "%016llx\n",
		       *(unsigned long long *) stp_info.ctnid);
}