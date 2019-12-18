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
struct probe_finder {int /*<<< orphan*/  cu_die; } ;
struct dwarf_callback_param {void* data; int retval; } ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf_getfuncs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct dwarf_callback_param*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_point_search_cb ; 

__attribute__((used)) static int find_probe_point_by_func(struct probe_finder *pf)
{
	struct dwarf_callback_param _param = {.data = (void *)pf,
					      .retval = 0};
	dwarf_getfuncs(&pf->cu_die, probe_point_search_cb, &_param, 0);
	return _param.retval;
}