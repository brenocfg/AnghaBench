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
typedef  int /*<<< orphan*/  kernel_section_t ;
typedef  int /*<<< orphan*/  kernel_mach_header_t ;

/* Variables and functions */
 int /*<<< orphan*/  _mh_execute_header ; 
 int /*<<< orphan*/ * getsectbynamefromheader (int /*<<< orphan*/ *,char const*,char const*) ; 

kernel_section_t *
getsectbyname(
    const char *segname,
    const char *sectname)
{
	return(getsectbynamefromheader(
		(kernel_mach_header_t *)&_mh_execute_header, segname, sectname));
}