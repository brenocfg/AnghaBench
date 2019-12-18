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
typedef  int /*<<< orphan*/  dtrace_objinfo_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_module_t ;

/* Variables and functions */
 char const* DTRACE_OBJ_EVERY ; 
 char const* DTRACE_OBJ_KMODS ; 
 char const* DTRACE_OBJ_UMODS ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/ * dt_module_from_object (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  dt_module_info (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dt_module_load (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int dt_set_errno (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
dtrace_object_info(dtrace_hdl_t *dtp, const char *object, dtrace_objinfo_t *dto)
{
	dt_module_t *dmp;

	if (object == DTRACE_OBJ_EVERY || object == DTRACE_OBJ_KMODS ||
	    object == DTRACE_OBJ_UMODS || dto == NULL)
		return (dt_set_errno(dtp, EINVAL));

	if ((dmp = dt_module_from_object(dtp, object)) == NULL)
		return (-1); /* dt_errno is set for us */

	if (dt_module_load(dtp, dmp) == -1)
		return (-1); /* dt_errno is set for us */

	(void) dt_module_info(dmp, dto);
	return (0);
}