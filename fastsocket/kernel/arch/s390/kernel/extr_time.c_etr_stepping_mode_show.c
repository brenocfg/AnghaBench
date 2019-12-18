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
struct sysdev_class {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  etr_eacr ; 
 scalar_t__ etr_mode_is_etr (int /*<<< orphan*/ ) ; 
 scalar_t__ etr_mode_is_pps (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t etr_stepping_mode_show(struct sysdev_class *class, char *buf)
{
	char *mode_str;

	if (etr_mode_is_pps(etr_eacr))
		mode_str = "pps";
	else if (etr_mode_is_etr(etr_eacr))
		mode_str = "etr";
	else
		mode_str = "local";
	return sprintf(buf, "%s\n", mode_str);
}