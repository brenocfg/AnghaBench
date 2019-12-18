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
struct pcd_unit {int /*<<< orphan*/  pi; } ;

/* Variables and functions */
 int pi_read_regr (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static inline int status_reg(struct pcd_unit *cd)
{
	return pi_read_regr(cd->pi, 1, 6);
}