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
struct TYPE_5__ {int ssid; int devno; } ;
struct TYPE_6__ {TYPE_1__ dev_id; } ;
struct TYPE_7__ {TYPE_2__ ccw; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_3__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  DASD_IPLDEV ; 
 int EINVAL ; 
 scalar_t__ IPL_TYPE_CCW ; 
 TYPE_4__ ipl_info ; 
 int /*<<< orphan*/  isxdigit (char) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int simple_strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int

dasd_busid(char **str, int *id0, int *id1, int *devno)
{
	int val, old_style;

	/* Interpret ipldev busid */
	if (strncmp(DASD_IPLDEV, *str, strlen(DASD_IPLDEV)) == 0) {
		if (ipl_info.type != IPL_TYPE_CCW) {
			pr_err("The IPL device is not a CCW device\n");
			return -EINVAL;
		}
		*id0 = 0;
		*id1 = ipl_info.data.ccw.dev_id.ssid;
		*devno = ipl_info.data.ccw.dev_id.devno;
		*str += strlen(DASD_IPLDEV);

		return 0;
	}
	/* check for leading '0x' */
	old_style = 0;
	if ((*str)[0] == '0' && (*str)[1] == 'x') {
		*str += 2;
		old_style = 1;
	}
	if (!isxdigit((*str)[0]))	/* We require at least one hex digit */
		return -EINVAL;
	val = simple_strtoul(*str, str, 16);
	if (old_style || (*str)[0] != '.') {
		*id0 = *id1 = 0;
		if (val < 0 || val > 0xffff)
			return -EINVAL;
		*devno = val;
		return 0;
	}
	/* New style x.y.z busid */
	if (val < 0 || val > 0xff)
		return -EINVAL;
	*id0 = val;
	(*str)++;
	if (!isxdigit((*str)[0]))	/* We require at least one hex digit */
		return -EINVAL;
	val = simple_strtoul(*str, str, 16);
	if (val < 0 || val > 0xff || (*str)++[0] != '.')
		return -EINVAL;
	*id1 = val;
	if (!isxdigit((*str)[0]))	/* We require at least one hex digit */
		return -EINVAL;
	val = simple_strtoul(*str, str, 16);
	if (val < 0 || val > 0xffff)
		return -EINVAL;
	*devno = val;
	return 0;
}