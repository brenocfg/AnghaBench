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
struct enic {int priv_flags; } ;

/* Variables and functions */
 int ENIC_SRIOV_ENABLED ; 

int enic_sriov_enabled(struct enic *enic)
{
	return (enic->priv_flags & ENIC_SRIOV_ENABLED) ? 1 : 0;
}