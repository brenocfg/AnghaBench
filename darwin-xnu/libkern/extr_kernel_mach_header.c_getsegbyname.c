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
typedef  int /*<<< orphan*/  kernel_segment_command_t ;

/* Variables and functions */
 int /*<<< orphan*/  _mh_execute_header ; 
 int /*<<< orphan*/ * getsegbynamefromheader (int /*<<< orphan*/ *,char const*) ; 

kernel_segment_command_t *
getsegbyname(const char *seg_name)
{
	return(getsegbynamefromheader(&_mh_execute_header, seg_name));
}