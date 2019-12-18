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
typedef  int /*<<< orphan*/  u16 ;
struct bnx2x {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_FUNC (struct bnx2x*) ; 
 int /*<<< orphan*/  mmiowb () ; 
 int /*<<< orphan*/  storm_memset_eq_prod (struct bnx2x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void bnx2x_update_eq_prod(struct bnx2x *bp, u16 prod)
{
	/* No memory barriers */
	storm_memset_eq_prod(bp, prod, BP_FUNC(bp));
	mmiowb(); /* keep prod updates ordered */
}