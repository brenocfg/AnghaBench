#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint_t ;
struct TYPE_4__ {scalar_t__ dtdv_id; scalar_t__ dtdv_scope; scalar_t__ dtdv_name; } ;
typedef  TYPE_1__ dtrace_difv_t ;
struct TYPE_5__ {scalar_t__ dtdo_varlen; scalar_t__ dtdo_strlen; char const* dtdo_strtab; TYPE_1__* dtdo_vartab; } ;
typedef  TYPE_2__ dtrace_difo_t ;

/* Variables and functions */

__attribute__((used)) static const char *
dt_dis_varname(const dtrace_difo_t *dp, uint_t id, uint_t scope)
{
	const dtrace_difv_t *dvp = dp->dtdo_vartab;
	uint_t i;

	for (i = 0; i < dp->dtdo_varlen; i++, dvp++) {
		if (dvp->dtdv_id == id && dvp->dtdv_scope == scope) {
			if (dvp->dtdv_name < dp->dtdo_strlen)
				return (dp->dtdo_strtab + dvp->dtdv_name);
			break;
		}
	}

	return (NULL);
}