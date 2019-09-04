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
typedef  int /*<<< orphan*/  processor_set_t ;
typedef  int /*<<< orphan*/  processor_set_name_t ;
typedef  int /*<<< orphan*/  ipc_port_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IP_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROCESSOR_SET_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ip_lock (int /*<<< orphan*/ ) ; 
 scalar_t__ ref_pset_port_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

processor_set_name_t
convert_port_to_pset_name(
	ipc_port_t	port)
{
	boolean_t r;
	processor_set_t pset = PROCESSOR_SET_NULL;

	r = FALSE;
	while (!r && IP_VALID(port)) {
		ip_lock(port);
		r = ref_pset_port_locked(port, TRUE, &pset);
		/* port unlocked */
	}
	return pset;
}