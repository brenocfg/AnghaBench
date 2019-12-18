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
typedef  scalar_t__ s16 ;
struct TYPE_2__ {int vbits; scalar_t__ leaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODATA ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 TYPE_1__ stp_info ; 
 int /*<<< orphan*/  stp_online ; 

__attribute__((used)) static ssize_t stp_leap_seconds_show(struct sysdev_class *class, char *buf)
{
	if (!stp_online || !(stp_info.vbits & 0x8000))
		return -ENODATA;
	return sprintf(buf, "%i\n", (int)(s16) stp_info.leaps);
}