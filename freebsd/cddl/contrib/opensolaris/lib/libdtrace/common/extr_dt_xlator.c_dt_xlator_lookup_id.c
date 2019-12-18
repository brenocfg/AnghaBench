#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t id_t ;
struct TYPE_3__ {size_t dt_xlatorid; int /*<<< orphan*/ ** dt_xlatormap; } ;
typedef  TYPE_1__ dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dt_xlator_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

dt_xlator_t *
dt_xlator_lookup_id(dtrace_hdl_t *dtp, id_t id)
{
	assert(id >= 0 && id < dtp->dt_xlatorid);
	return (dtp->dt_xlatormap[id]);
}