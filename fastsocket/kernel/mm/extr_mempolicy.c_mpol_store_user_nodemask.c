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
struct mempolicy {int flags; } ;

/* Variables and functions */
 int MPOL_F_RELATIVE_NODES ; 
 int MPOL_F_STATIC_NODES ; 

__attribute__((used)) static inline int mpol_store_user_nodemask(const struct mempolicy *pol)
{
	return pol->flags & (MPOL_F_STATIC_NODES | MPOL_F_RELATIVE_NODES);
}