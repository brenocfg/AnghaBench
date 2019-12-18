#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sysdev_attribute {int dummy; } ;
struct sys_device {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_3__ {int psc0; int psc1; } ;
struct TYPE_4__ {TYPE_1__ esw; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENODATA ; 
 TYPE_2__ etr_port0 ; 
 struct sys_device etr_port0_dev ; 
 int /*<<< orphan*/  etr_port0_online ; 
 int /*<<< orphan*/  etr_port1_online ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

__attribute__((used)) static ssize_t etr_mode_code_show(struct sys_device *dev,
				struct sysdev_attribute *attr, char *buf)
{
	if (!etr_port0_online && !etr_port1_online)
		/* Status word is not uptodate if both ports are offline. */
		return -ENODATA;
	return sprintf(buf, "%i\n", (dev == &etr_port0_dev) ?
		       etr_port0.esw.psc0 : etr_port0.esw.psc1);
}