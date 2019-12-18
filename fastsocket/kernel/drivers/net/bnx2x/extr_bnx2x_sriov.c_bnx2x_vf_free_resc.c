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
struct bnx2x_virtf {int /*<<< orphan*/  state; int /*<<< orphan*/  alloc_resc; } ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VF_FREE ; 
 int /*<<< orphan*/  bnx2x_iov_static_resc (struct bnx2x*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void bnx2x_vf_free_resc(struct bnx2x *bp, struct bnx2x_virtf *vf)
{
	/* reset the state variables */
	bnx2x_iov_static_resc(bp, &vf->alloc_resc);
	vf->state = VF_FREE;
}