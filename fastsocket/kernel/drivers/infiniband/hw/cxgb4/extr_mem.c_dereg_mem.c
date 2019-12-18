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
typedef  int /*<<< orphan*/  u32 ;
struct c4iw_rdev {int dummy; } ;

/* Variables and functions */
 int write_tpt_entry (struct c4iw_rdev*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dereg_mem(struct c4iw_rdev *rdev, u32 stag, u32 pbl_size,
		     u32 pbl_addr)
{
	return write_tpt_entry(rdev, 1, &stag, 0, 0, 0, 0, 0, 0, 0UL, 0, 0,
			       pbl_size, pbl_addr);
}