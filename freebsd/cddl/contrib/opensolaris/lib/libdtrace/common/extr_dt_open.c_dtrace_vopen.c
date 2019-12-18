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
typedef  int /*<<< orphan*/  dtrace_vector_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;

/* Variables and functions */
 int /*<<< orphan*/ * dt_vopen (int,int,int*,int /*<<< orphan*/  const*,void*) ; 

dtrace_hdl_t *
dtrace_vopen(int version, int flags, int *errp,
    const dtrace_vector_t *vector, void *arg)
{
	return (dt_vopen(version, flags, errp, vector, arg));
}