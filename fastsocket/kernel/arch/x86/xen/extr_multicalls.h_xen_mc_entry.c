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
struct multicall_space {int dummy; } ;

/* Variables and functions */
 struct multicall_space __xen_mc_entry (size_t) ; 
 int /*<<< orphan*/  xen_mc_batch () ; 

__attribute__((used)) static inline struct multicall_space xen_mc_entry(size_t args)
{
	xen_mc_batch();
	return __xen_mc_entry(args);
}