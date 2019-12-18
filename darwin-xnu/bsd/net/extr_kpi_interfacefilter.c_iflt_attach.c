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
struct iff_filter {int dummy; } ;
typedef  int /*<<< orphan*/  interface_filter_t ;
typedef  int /*<<< orphan*/ * ifnet_t ;
typedef  int /*<<< orphan*/  errno_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  dlil_attach_filter (int /*<<< orphan*/ *,struct iff_filter const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

errno_t
iflt_attach(
	ifnet_t interface,
	const struct iff_filter *filter,
	interface_filter_t *filter_ref)
{
	if (interface == NULL) return ENOENT;
		
	return dlil_attach_filter(interface, filter, filter_ref, 0);
}