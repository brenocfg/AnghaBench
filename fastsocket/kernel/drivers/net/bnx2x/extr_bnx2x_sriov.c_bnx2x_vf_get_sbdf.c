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
typedef  int u32 ;
struct bnx2x_virtf {int devfn; int bus; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static inline void bnx2x_vf_get_sbdf(struct bnx2x *bp,
			      struct bnx2x_virtf *vf, u32 *sbdf)
{
	*sbdf = vf->devfn | (vf->bus << 8);
}